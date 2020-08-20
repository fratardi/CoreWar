ASM="../asm"
COREWAR="../corewar"
ZAZ="42_corewar"
ACTION1="\n\033[1;96m Executing :"
ACTION2="\n\033[1;95m Executing :"
ACTION3="\n\033[1;35m Executing :"
NC="\033[0m\n"
DUMP="./dump_checker.sh"

#	echo "$ACTION1 $ASM $arg $NC"
#	$ASM $arg
#	cor=`echo $arg | sed 's/\(.*\.\)s/\1cor/'`

for champ1 in $@
do
	echo "$ACTION1 $DUMP $COREWAR 30000 $champ1 $NC"
	$DUMP $COREWAR 30000 $champ1
done
