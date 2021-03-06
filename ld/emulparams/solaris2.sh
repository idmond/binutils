# If you change this file, please also look at files which source this one:
# cgc32_sparc_sol2.sh, cgc64_sparc_sol2.sh, cgc_i386_sol2.sh,
# cgc_x86_64_sol2.sh.

# The Solaris 2 ABI requires that two local symbols are present in every
# executable and shared object.
# Cf. Linker and Libraries Guide, Ch. 2, Link-Editor, Generating the Output
# File, p.63.
TEXT_START_SYMBOLS='_START_ = .;'
OTHER_END_SYMBOLS='_END_ = .;'
