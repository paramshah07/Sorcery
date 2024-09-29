
## Game Features

- **Card Types**: There are four main card types: Ritual, Spell, Minion, and Enchantment. Each has unique abilities and interactions.
- **Players**: Two players, each with their own deck, hand, and life points. Players can draw cards, play cards, and utilize minion abilities, among other actions.
- **Board**: The game is played on a shared board, with sections for minions, rituals, and graves for both players. The board manages game flow, including turns and triggering abilities.
- **Special Abilities**: Cards like Bone Golem, Master Summoner, and Apprentice Summoner have special abilities that are managed by a dedicated class.

## Design

The game architecture follows a modular and object-oriented approach, promoting code reuse and maintainability:

- **Encapsulation**: Data is encapsulated within classes like `Player`, `Card`, and `Board`, ensuring controlled access and modification of game states.
- **Inheritance**: A clear class hierarchy allows common functionality to be inherited by subclasses. For example, the `Card` class is the base class for specific card types like `Minion` and `Spell`.
- **Polymorphism**: Dynamic card interactions are handled through polymorphism. Each card type can override shared methods to implement unique behaviors, enhancing flexibility.
- **Design Patterns**: We utilized design patterns such as Composite for board management and Decorator for enchantments, simplifying the game's complexity.

## UML Diagram

Below is the UML diagram representing the structure of the game:

![UML Diagram](uml-final.pdf)
