{
  "targets": [
    {
      "target_name": "logicsim",
	  "include_dirs": [
		"src",
		"src/components"
	  ],
      "sources": [
		"src/project.cpp",
		"src/barrier.h",
		"src/board.cpp",
		"src/board.h",
		"src/component.cpp",
		"src/component.h",
		"src/events.h",
		"src/input.cpp",
		"src/input.h",
		"src/link.cpp",
		"src/link.h",
		"src/output.cpp",
		"src/output.h",
		"src/spinlock_barrier.h",
		"src/components/and.h",
		"src/components/clk.h"
	  ]
    }
  ]
}