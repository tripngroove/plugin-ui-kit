# plugin-ui-kit notes for Claude

- This is the shared look of tripngroove's plugins (first: PatternArp), consumed by each plugin as a git submodule at `libs/plugin-ui-kit`. A JUCE module `tng_ui`, namespace `tng` / `tng::theme`.
- The owner is not a programmer: explain changes in plain language.
- Follow STYLE_GUIDE.md; update it when a UI decision changes or a new one is made.
- Only code any plugin could use belongs here. Nothing about one plugin's data (patterns, lanes...).
- A change here reaches a plugin only when that plugin moves its submodule to the new commit. Check each plugin still builds and looks the same (PatternArp's smoke test can save editor snapshots: PATTERNARP_SNAPSHOT, PATTERNARP_STATE).
