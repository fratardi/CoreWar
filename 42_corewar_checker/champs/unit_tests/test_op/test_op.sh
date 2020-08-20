ASM="../../../../asm"
ASM42="../../../resources/42_asm_mac"
COREWAR="../../../../corewar"
ZAZ="../../../42_corewar"
ACTION1="\n\033[1;96m Executing :"
ACTION2="\n\033[1;95m Executing :"
ACTION3="\n\033[1;35m Executing :"
NC="\033[0m\n"
cor=""

for arg in $@
do
	echo "$ACTION1 $ASM $arg $NC"
	$ASM $arg
	cor=`echo $arg | sed 's/\(.*\.\)s/\1cor/'`
	echo "$ACTION2 $COREWAR -v 1 $cor $NC"
	$COREWAR -v 1 $cor
	echo "$ACTION3 $ZAZ -v 29 $cor $NC"
	$ZAZ -v 29 $cor
	echo "\n"
done
rm -rf *.cor
