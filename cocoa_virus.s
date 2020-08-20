.name		"Cocoa_Virus"
.comment	"La vie c'est triste, les pandemies ca tue, mais le cocoa c'est bon."

				ld %-128, r3
				ld %8, r5
				ld %10, r4
				ld %-500, r15
				ld %0, r2
				sti r1, %:sneaky, %1
				zjmp %:fork
sneaky:
				live %0
				sti r2, %:sneaky, %0
				sti r13, r15, r2
				zjmp	%-505

fork:
				fork %:zukzuk
zagzag:
				ld %0, r2
				ld %190056965, r9
				ld %50465279, r10
				ld %190057477, r11
				ld %67240447, r12
				ld %190056453, r7
				ld %50465279, r8
				ld %190056207, r13
				ld %0, r6
				zjmp %:sneaky

zukzuk:
				ld %4, r2
				ld %34296839, r9
				ld %2064584463, r10
				ld %34296841, r11
				ld -115, r12
				ld %34296843, r7
				ld %2064584463, r8
				ld %34209285, r13
				ld %0, r6
				zjmp %:sneaky
