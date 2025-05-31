# Crystal Mountain Campaign Content Summary

## Entities
| ID              | Name             | Description                  | Base Stats (STRENGTH/DEXTERITY/INSIGHT/LUCK) | Walkable | Sprite         | AI   |
|-----------------|------------------|------------------------------|---------------------------------------------|----------|----------------|------|
| player_crusader | Crusader         | A brave warrior of light.    | 10 / 5 / 3 / 2                              | No       | player_male    | -    |
| rat             | Rat              | A small but vicious rodent.  | 1 / 2 / 1 / 1                               | No       | rat            | -    |
| naked_goblin    | Naked Goblin     | A weak goblin without armor. | 3 / 2 / 1 / 1                               | No       | naked_goblin   | -    |
| coward_goblin   | Coward Goblin    | A goblin that prefers to flee.| 4 / 3 / 2 / 2                              | No       | coward_goblin  | -    |
| armored_goblin  | Armored Goblin   | A goblin with heavy armor.   | 6 / 4 / 2 / 1                               | No       | armored_goblin | -    |
| chair           | Wooden Chair     | A simple wooden chair.       | -                                           | Yes      | chair_w        | none |
| alchemy_table   | Alchemy Table    | A table for alchemical use.  | -                                           | Yes      | alchemy_table  | none |
| book_shelf      | Book Shelf       | A shelf filled with books.   | -                                           | Yes      | book_shelf     | none |

## Items
| ID          | Name          | Description                  | Attributes (Stat Changes)         | Requirements (Min Attributes) | Slot   | Sprite       |
|-------------|---------------|------------------------------|-----------------------------------|-------------------------------|--------|--------------|
| basic_sword | Basic Sword   | A simple sword for beginners.| PHYSICAL_DAMAGE: 5               | STRENGTH: 1                   | weapon | basic_sword  |
| claymore    | Claymore      | A large two-handed sword.    | PHYSICAL_DAMAGE: 10, CRITICAL_CHANCE: 2 | STRENGTH: 5                   | weapon | claymore     |
| great_sword | Great Sword   | A massive sword for warriors.| PHYSICAL_DAMAGE: 15, CRITICAL_CHANCE: 5 | STRENGTH: 10                  | weapon | great_sword  |
| basic_helm  | Basic Helm    | A simple helmet for protection.| ARMOR: 2                        | STRENGTH: 1                   | head   | basic_helm   |
| knight_helm | Knight Helm   | A sturdy helmet for knights. | ARMOR: 5, STRENGTH: 2            | STRENGTH: 3                   | head   | knight_helm  |
| basic_staff | Basic Staff   | A simple staff for mages.    | MAGICAL_DAMAGE: 5, INSIGHT: 2    | INSIGHT: 3                    | weapon | basic_staff  |

## Tiles
| ID          | Name          | Walkable | Sprite       |
|-------------|---------------|----------|--------------|
| floor_tile1 | Floor Tile    | Yes      | floor_tile1  |
| wall_tile1  | Wall Tile     | No       | wall_tile1   |
| chair_w     | Wooden Chair  | No       | chair_w      |
| alchemy_table | Alchemy Table | No      | alchemy_table |
| book_shelf  | Book Shelf    | No       | book_shelf   |

## Structures
| ID              | Name             | Description                  | Composition (Entities/Tiles)                | Placement Rules |
|-----------------|------------------|------------------------------|---------------------------------------------|-----------------|
| library_corner  | Library Corner   | A corner with bookshelves.   | book_shelf x 2, chair x 1                   | Only on floors  |
| alchemy_lab     | Alchemy Lab      | A lab with alchemy tables.   | alchemy_table x 2, chair x 1                | Only on floors  |

## Levels
| ID          | Name          | Type          | Size (Min/Max)         | Room Density | Floor Tile   | Wall Tile   | Rooms Included         | Entities Included       |
|-------------|---------------|---------------|------------------------|--------------|--------------|-------------|------------------------|-------------------------|
| crypts      | Crypts        | Procedural    | 20x20 / 30x30          | 0.5          | floor_tile1  | wall_tile1  | alchemy_chamber (40%)  | rat (50%), naked_goblin (40%), coward_goblin (30%), armored_goblin (20%) |
| library     | Library       | Procedural    | 20x20 / 20x20          | 0.5          | floor_tile1  | wall_tile1  | small_library (40%)    | rat (50%), naked_goblin (40%), coward_goblin (30%), armored_goblin (20%) |