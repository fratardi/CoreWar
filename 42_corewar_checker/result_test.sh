ASM="../asm"
COREWAR="../corewar"
ZAZ="./42_corewar"
ACTION1="\n\033[1;96m Executing :"
ACTION2="\n\033[1;95m Executing :"
ACTION3="\n\033[1;35m Executing :"
NC="\033[0m\n"
DUMP="./dump_checker.sh"

#	echo "$ACTION1 $ASM $arg $NC"
#	$ASM $arg
#	cor=`echo $arg | sed 's/\(.*\.\)s/\1cor/'`

usage_and_exit()
{
	printf "%s\n" "Usage:  $0 <rounds> [player1 player2 ...]"
	printf "%s\n" ""
	printf "%s\n" "     <rounds>     how many random match"
	printf "%s\n" "     [player]     list of players to use"
	exit 1
}

if [ $# -lt 2 ]; then
	usage_and_exit
fi

NBR_ROUNDS=$1
shift
for (( c=0; c < $NBR_ROUNDS; c++ ))
do
	CHAMP1=${@: $(($RANDOM % ($# -1) )) : 1}
	CHAMP2=${@: $(($RANDOM % ($# -1) )) : 1}
	CHAMP3=${@: $(($RANDOM % ($# -1) )) : 1}
	echo "$ACTION1 $COREWAR $CHAMP1 $CHAMP2 $CHAMP3 $NC"
	$COREWAR $CHAMP1 $CHAMP2 $CHAMP3 | grep "GRAND GAGNANT"
	echo "$ACTION1 $ZAZ $CHAMP1 $CHAMP2 $CHAMP3 $NC"
	$ZAZ $CHAMP1 $CHAMP2 $CHAMP3 | grep "has won"
	echo "\n"
done


