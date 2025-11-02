# Clook — High-Level Design

Clook is a time tracking and progress journaling application.  
It centers around clear, goal-oriented entities that record both *quantitative progress* (time spent) and *qualitative reflection* (notes and milestones).

---

## 🧭 Overview

Clook’s core logic is built around four main classes:

- **Milestone** — represents a large, overarching goal.
- **Attempt** — represents a focused session or smaller target contributing to a Milestone.
- **Timer** — handles precise time measurement for each Attempt.
- **Notes** — stores contextual reflections or textual logs.
- **Storage** — manages persistence and data retrieval for all objects.

Together, they form the structure of a personal progress-tracking system.

---

## 🧩 Class Responsibilities

### **Milestone**
- Represents a large goal that may take multiple Attempts to complete.
- Owns its own Timer to measure elapsed work time.
- Owns and manages a collection of related Attempts.
- Provides aggregate statistics (total time, completion progress).
- May have its own Notes for high-level reflections.

**Relationships**
- **Has many** Attempts.
- **Owns one** Timer.
- **Has one** Notes object (optional).
- **Interacts with** Storage for saving/loading state.

---

### **Attempt**
- Represents a single working session or specific objective tied to a Milestone.
- Holds Notes describing what happened in that session.
- Reports its data to the Milestone or Storage when completed.

**Relationships**
- **Belongs to** one Milestone.
- **Has one** Notes.
- **Interacts with** Storage for persistence.

---

### **Timer**
- Handles timing operations: start, pause, resume, stop.
- Tracks total elapsed duration accurately, supporting multiple intervals.
- Independent utility; unaware of Milestones or Attempts.
- Provides timing data to its owner (usually Attempt).

**Relationships**
- **Owned by** Attempt.
- **Independent** of higher-level logic.
- **Serializable** through its owning object.

---

### **Notes**
- Stores written entries tied to an Attempt or Milestone.
- Keeps a list of timestamped textual logs (journal-style).
- Optional tags or categories for organization.
- Persistent across runs through Storage.

**Relationships**
- **Owned by** Milestone or Attempt.
- **Interacts with** Storage for saving/loading.
- **Purely contextual**, does not affect computation.

---

### **Storage**
- Centralized system for saving and loading application data.
- Abstracts file I/O or database operations from the main logic.
- Ensures data integrity and version consistency.
- Supports both complete and incremental saves.

**Relationships**
- **Interacts with** all major entities for persistence.
- **Owns** no business logic — purely manages data.
- Future extensions: backup system, database adapter, or cloud sync.

---

## 🔁 Class Interactions

```mermaid
classDiagram
    class Milestone {
        - vector<Attempt> attempts
        - Timer timer
        - Notes notes
        + addAttempt()
        + getProgress()
    }

    class Attempt {
        - Notes notes
        + start()
        + pause()
        + stop()
        + getElapsed()
    }

    class Timer {
        - start_time
        - accumulated
        + start()
        + pause()
        + elapsed()
    }

    class Notes {
        - vector<NoteEntry> entries
        + addNote()
        + listNotes()
    }

    class Storage {
        + saveAll()
        + loadAll()
        + saveMilestone()
    }

    Milestone --> Attempt : "has many"
    Attempt --> Timer : "owns"
    Attempt --> Notes : "has"
    Milestone --> Notes : "has"
    Milestone --> Storage : "serialized by"
    Storage --> Attempt : "saves/loads"
    Storage --> Notes : "saves/loads"

🧠 Runtime Flow Example

1. User starts an Attempt under a Milestone.
2. The Timer begins tracking active duration.
3. When paused or stopped, Timer reports total elapsed time to the Attempt.
4. User adds a Note describing progress.
5. On exit, Storage serializes all Milestones, Attempts, Timers, and Notes to disk.
6. On next launch, Storage reconstructs the full state.

🧩 Design Principles

Encapsulation: Each class has a focused purpose.
Separation of concerns: Timing, persistence, and journaling are distinct domains.
Persistence-first design: Data survives across runs.
Scalability: Ready for GUI expansion or database backend.
Human-centered: Encourages reflection, not just data collection.

📈 Future Extensions

- Add benchmarking / performance metrics to Timer.
- Introduce statistics view (e.g., weekly summaries).
- Enable data export/import in common formats.
- Build GUI front-end (Qt/QML) backed by same logic.

---