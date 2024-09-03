# Contributing to Arduino Pandemic

Thank you for considering contributing to our project! We appreciate your efforts to improve the codebase. Please follow the guidelines outlined below to ensure that your contributions align with the project’s standards.

## Table of Contents
1. [Code Structure](#code-structure)
2. [Functionalization](#functionalization)
3. [Branchless Code](#branchless-code)
4. [Comments](#comments)
5. [Testing](#testing)
6. [Pull Requests](#pull-requests)
7. [Code of Conduct](#code-of-conduct)

## Code Structure

- **Organize** your code into functions that perform specific, discrete tasks.
- **Modularity** is crucial: if a function can be reused, place it in an appropriate module or library file.
- **File Naming**: Use clear and descriptive names for files and directories to reflect their contents and roles within the project.

## Functionalization

- **Single Responsibility**: Each function should perform a single, well-defined task.
- **Input and Output**: Functions should take inputs via parameters and return outputs. Avoid using global variables unless absolutely necessary.
- **Function Length**: Keep functions concise. If a function exceeds 30 lines, consider refactoring it into smaller functions.

### Example:

```cpp
void initializeLEDs() {
  // Initialize the LED strip with default settings
  // Set all LEDs to off state and apply configurations
}  // Function initializes the LED strip
```

## Branchless Code

- **Predictable Execution**: Aim to write code with as few branches (e.g., `if`, `else`, `switch`) as possible.
- **Use Lookup Tables**: Where appropriate, replace conditional logic with lookup tables or mathematical operations.
- **Avoid Deep Nesting**: Keep the nesting level shallow by early returns or by refactoring complex conditions into simpler functions.

### Example:

Instead of:

```cpp
void updateLEDColor(int condition) {
  if (condition == 1) {
    setColorRed();
  } else if (condition == 2) {
    setColorGreen();
  } else {
    setColorBlue();
  }
}  // Function to update LED color based on the condition
```

Use:

```cpp
void updateLEDColor(int condition) {
  const Color colors[] = {BLUE, RED, GREEN};
  setColor(colors[condition % 3]);
}  // Function updates LED color using a lookup table
```

## Comments

- **After Function Closing Bracket**: All comments should be placed immediately after the closing bracket of a function.
- **Brief and Descriptive**: Comments should succinctly describe what the function does without repeating the function name or parameters.
- **Avoid Inline Comments**: Place comments after functions, not within the function body unless absolutely necessary.

### Example:

```cpp
void initializeButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}  // Function initializes the button with pull-up resistor
```

## Testing -- To be created

- **Unit Tests**: Write unit tests for every new function. Ensure that all edge cases are covered.
- **Hardware Testing**: If your changes affect hardware behavior, test them on real hardware and document the results.
- **CI Integration**: Ensure that your code passes all Continuous Integration (CI) checks before submitting a pull request.

## Pull Requests

- **One Change per Pull Request**: Each pull request should be focused on a single change or improvement.
- **Descriptive Titles**: Use clear and descriptive titles for your pull requests.
- **Commit Messages**: Write concise and informative commit messages.
- **Review Process**: Be responsive during the review process. Address feedback promptly and update your pull request as needed.

## Code of Conduct

Please adhere to our [Code of Conduct](link-to-code-of-conduct) to maintain a welcoming and inclusive environment for all contributors.

### Thanks!

We appreciate your contributions and your efforts to maintain the quality and functionality of this project. Happy coding!

If you have any questions about this project, contributing to it, or why I've made the choices I have, please don't be a stranger! 

You can e-mail me at [canceb@gmail.com](canceb@gmail.com)
