# Clook

A lightweight personal productivity tool for structuring goal‑driven work. Clook helps break long‑term objectives into intentional, timed effort cycles with built‑in breaks and reflection prompts.

## Features

* **Milestones**: Define overarching goals (e.g., "Learn C++").
* **Attempts**: Create incremental work sessions tied to a Milestone.
* **Loop system**: Specify how many focused loops and their duration.
* **Break cycles**: Automatic breaks between loops with user prompts.
* **Progress tracking**: Track effort toward each Milestone.

## Core Concept

A Milestone represents a long‑term goal. An Attempt represents a focused work block toward that goal, consisting of multiple timed loops. Each loop is a unit of uninterrupted focus, followed by a break. Clook guides you through these cycles until the Attempt target is reached.

Example:

* Milestone: Learn C++
* Attempt: Learn operator overloading
* Loops: 3
* Loop duration: 25 minutes each

Clook runs 3 cycles of 25‑minute focus + breaks, prompting you before starting each loop.

## Installation

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

After building, the `bin/` directory will contain an executable named `clook-cli`.
It is recommended to create a shell alias to run it conveniently from the terminal.

Example:

```bash
# ~/.bashrc or ~/.zshrc
alias clook="/path/to/Clook/bin/clook-cli"
```

Reload your shell and run:

````bash
clook
````

## Usage - TODO

````bash

````