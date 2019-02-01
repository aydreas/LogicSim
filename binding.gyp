{
  "targets": [
    {
      "target_name": "logicsim",
	  "include_dirs": [
		"src",
		"src/components",
		"<!(node -e \"require('nan')\")"
	  ],
      "sources": [
		"src/project.cpp",
		"src/barrier.h",
		"src/board.cpp",
		"src/board.h",
		"src/component.cpp",
		"src/component.h",
		"src/user_input_component.h",
		"src/events.h",
		"src/input.cpp",
		"src/input.h",
		"src/link.cpp",
		"src/link.h",
		"src/output.cpp",
		"src/output.h",
		"src/spinlock_barrier.h",
		"src/components/and.h",
		"src/components/button.h",
		"src/components/clk.h",
		"src/components/delay.h",
		"src/components/not.h",
		"src/components/or.h",
		"src/components/switch.h",
		"src/components/xor.h"
		
	  ]
    }
  ]
}