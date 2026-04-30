1. **Task 1: Skill & Job Overhaul**
   - In `HunterRPG/Skill.h` and `HunterRPG/Skill.cpp`:
     - Add `int priority;` to `Skill` class, default 0. Update constructor `Skill(std::string name, Trigger trigger, int baseProbability, int priority = 0)`.
     - Implement `BasicAttack` class deriving from `Skill`. It triggers `ON_ATTACK`, `baseProbability = 100`, `priority = 0`. Its execute applies `attack()` damage.
     - Update `HealSkill`, `HeavyStrike`, `CounterAttack` constructors to set `priority = 1`. Update `HeavyStrike` power/probability, etc. if not aligned (it's 1.5x damage, 40 prob currently. I will align HeavyStrike: maybe 2.0x damage at 50% prob, based on prompt: "HeavyStrike deals 2.0x damage at 50% prob").
   - In `HunterRPG/Job.h`:
     - Modify `Job` constructors to push `BasicAttack` AND their signature skill. E.g., `MeleeDealer` pushes `BasicAttack` and `HeavyStrike`.
     - Since `NoneJob` has no signature, it will just have `BasicAttack`.

2. **Task 2: Elite Monster System**
   - In `HunterRPG/Monster.h` and `HunterRPG/Monster.cpp`:
     - Add `bool isElite` to `Monster` class, initialized in constructor or a default false. Add `std::vector<std::unique_ptr<Skill>> skills` or similar to handle its skills. Or actually, if it's dynamic, maybe give `Monster` a `vector<unique_ptr<Skill>> skills` and override `getActiveSkills` to return them.
     - Add `Monster::makeElite(std::unique_ptr<Skill> sigSkill)` or handle it during instantiation. Prompt: "In Game::turnLoop, when spawning monsters, give each a 15% chance to be an Elite".
     - Elite monsters prepend "[Elite] " to their name. Multiply base stats by 1.5x. Give them a signature skill based on `Monster::naming()` result (e.g. `code[2]` which is the element index).
     - Need to ensure `Monster` class has an implementation for `getActiveSkills()` since `Monster` currently just inherits `Character`'s empty `getActiveSkills()` which returns `{}`. I'll add `std::vector<std::unique_ptr<Skill>> skills` to `Monster` and implement `getActiveSkills()` like `Job` does. And add a basic attack to monsters too! (Non-elite get `BasicAttack`, Elite get `BasicAttack` + signature). Wait, maybe all monsters get `BasicAttack`? Yes, "even basic attacks are skills".

3. **Task 3: Loot Bias System**
   - In `HunterRPG/Player.h` and `HunterRPG/Player.cpp`:
     - Update `generateLoot(int price)` to `generateLoot(int price, int bias = 0)`.
     - `bias` is added as a flat bonus to every stat rolled in the loot. For instance, if `bias` is 5, `newItem.atk += 5`, `newItem.def += 5`, etc. Or does it add to `newItem` stats directly once, or every roll? The prompt says "The bias value should be added as a flat bonus to every stat rolled in the loot." I'll add the bias to each `stat` block: e.g. `newItem.atk += 10 + bias`. Wait, "added as a flat bonus to every stat rolled" or "added to every stat of the generated loot"? Let's do:
       ```cpp
       newItem.atk += bias;
       newItem.def += bias;
       newItem.spd += bias;
       newItem.maxHp += bias;
       ```
       or add it when the stat is rolled: `case 0: newItem.atk += 10 + bias; break;`. Let's see. Better to add flat to each roll or just flat once? "added as a flat bonus to every stat rolled in the loot." -> `case 0: newItem.atk += 10 + bias;` no, wait, `case 3: newItem.maxHp += 100 + bias*10;`? Actually, a flat bonus to every stat at the end is easiest: `atk += bias`, etc. Or `atk += 10 + bias`? I will probably just add `bias` to each of `newItem`'s 4 stats once at the end. Actually, "added as a flat bonus to every stat rolled in the loot" -> every time a stat is "rolled", it gets a bias? I'll probably just add it to the final stats. Oh, wait, maybe `rank` loop: `case 0: newItem.atk += 10; break;` ... then after loop `newItem.atk += bias; newItem.def += bias; ...`. I will do this.
     - When Elite is defeated, `bias = 10`.

4. **Task 4: Bidirectional LUCK Logic**
   - In `HunterRPG/Battle.cpp`, the prompt asks to use `checkSkillProbability` for ALL skill checks.
   - Wait, `evaluateTriggers` currently does `checkSkillProbability(skill->baseProbability, effectiveLuck)`.
   - The battle logic already uses `checkSkillProbability`. The critical part is:
     "When an ally (Player) uses a skill, use `player->getLuck()`. When a monster uses a skill, use `-player->getLuck()`. This ensures Player LUCK benefits allies and penalizes enemies."
   - The current code:
     `evaluateTriggers(defender, Trigger::ON_DEFEND, defenderLuck);`
     It's passed `defenderLuck`.
     For monster, `evaluateTriggers(&monster, Trigger::ON_TURN_START, -player.getLuck());`
     But what about `ON_ATTACK` and `ON_DEFEND`?
     Currently:
     `executeAttackPhase(&player, &monster, player.getLuck(), -player.getLuck(), ...)`
     `executeAttackPhase(&monster, &player, -player.getLuck(), player.getLuck(), ...)`
     Ah! Wait, `executeAttackPhase` calls `evaluateTriggers` for `defender` and `attacker`. So the luck logic is ALREADY mostly there?
     Let's check `Battle.cpp` carefully. It seems already bidirectional!
     But wait, is `checkSkillProbability` used for ALL skill checks?
     Wait, what about the trigger in `Battle.cpp` where basic attack is triggered? Basic attack has 100 base probability.
     Actually, Task 4 says "Ensure checkSkillProbability in Battle.cpp is used for ALL skill checks." Wait! Maybe the basic attack execution should use it? Basic attack `ON_ATTACK` has `baseProbability = 100`. It will always be true unless luck somehow makes it fail? `-player.getLuck()` with baseProb=100 won't fail because `checkSkillProbability` says `if (rand() % 100 >= baseProb) return false;` wait! `rand() % 100` goes from 0 to 99. `baseProb` 100 means `rand() % 100 >= 100` is always false, so it always returns true. So it's safe.

5. **Task 5: Update README.md (v4.0)**
   - Update README version and features.
