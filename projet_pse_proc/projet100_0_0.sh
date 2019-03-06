#!/bin/sh

#              fonction mod_interactif
#############################################################
mod_interactif(){
	while [ 1 -ne 0 ]
	do
		echo ">"
		read cmd
		echo $cmd>$dircour/cmd.txt
		opt=$(cat $dircour/cmd.txt | cut -f1 -d " ")
		arg1=$(cat $dircour/cmd.txt | cut -f2 -d " ")
		arg2=$(cat $dircour/cmd.txt | cut -f3 -d " ")
		arg3=$(cat $dircour/cmd.txt | cut -f4 -d " ")
		rm $dircour/cmd.txt
		case $opt in
			top) echo $arg1 | egrep '^[0-9]+$' >/dev/null 2>&1
				 if [ $? -eq 0 -a $(echo "$arg1" | awk '{print substr($0,1,1);exit}') != 0 ]
					then
						nblignes=$arg1
				 else
					echo "Argument d'option -n est NaN">&2
				 fi
			;;
			sort) for var in mem cpu start prio
				  do
					if [ "$arg1" = "$var" ]
					then
						sortopt=$arg1
						getcode
					fi
				  done
			;;
			cd) if [ -d $arg1 ]
				then
					dir=$arg1
					cd $arg1
				else
					echo "Option -d prend en argument le nom de repertoire existante.">&2
				fi
			;;
			kill)
				grep $arg1 $dircour/srcpids.txt >/dev/null 2>&1
				if [ $? -eq 0 -a -d /proc/$arg1 ]
					then
					lignecour=$(grep $arg1 $dircour/srcpids.txt)
					killcodecour=$(echo $lignecour | cut -f2 -d " ")
					case $killcodecour in
						1) killcodecour=15
						;;
						15) killcodecour=9
						;;
					esac
					sed "s/$arg1.*/$arg1 $killcodecour/" $dircour/srcpids.txt>$dircour/pids.txt
					cat $dircour/pids.txt>$dircour/srcpids.txt
				elif [ $? -eq 1 -o $? -eq 2 -a -d /proc/$arg1 ]
					then
					killcodecour=1
					echo "$arg1 $killcodecour">>$dircour/srcpids.txt
				fi
				kill -$killcodecour $arg1
			;;
			renice) if [ "$arg2"="-p" ]
					then
						renice $arg1 $arg2 $arg3
					else
						echo "usage: renice <prio> -p <PID>"
					fi
			;;
			exit)
				rm  $dircour/srcpids.txt $dircour/pids.txt 
				exit 0
			;;
			?) 
			;;
		esac
		affichage_proc
		affichage_fichier
	done
}
#              fonction affichage_fichier(arg=dir)
#############################################################
affichage_fichier()
{
	echo "Les 5 fichiers occupant le plus d'espace disque :"
	echo "SIZE(o)  FILE"
	find $dir -type f -exec du -ba {} + | sort -rn | head -$nblignes
#-exec command {} +
#              This  variant of the -exec action runs the specified command on the selected files, but the command line is built
 #             by appending each selected file name at the end; the total number of invocations of the command will be much less
  #            than  the  number of matched files.  The command line is built in much the same way that xargs builds its command
   #           lines.  Only one instance of `{}' is allowed within the command.  The command is executed in the starting  direc‐
    #          tory.   If find encounters an error, this can sometimes cause an immediate exit, so some pending commands may not
     #         be run at all.  This variant of -exec always returns true.

}
#              fonction affichage_proc(arg=sortopt)
########################################################
affichage_proc()
{
	echo "Processus: $nblignes processus tries par $sortstring"
	echo "PID    CPU    PRIO  VSIZE  STARTTIME"
	ps=$(ls /proc | grep -o [0-9]*)
	hz=$(getconf CLK_TCK)
	for touts in $ps
	do
		if [ -d "/proc/$touts" ]
				then
					$(cat /proc/$touts/stat | sed 's/(.*)/!/'> $dircour/source.txt)
					
					PID=$(cat $dircour/source.txt | cut -f1 -d " ")
					PRIO=$(cat $dircour/source.txt | cut -f18 -d " ")
 					vsize=$(cat $dircour/source.txt | cut -f23 -d " ")
					VSIZE=$(expr $vsize / 8388608)
					#TIME
					starttimeJ=$(cat $dircour/source.txt | cut -f22 -d " ")
					starttimeS=$(expr $starttimeJ / $hz)
					uptemps=$(cat /proc/uptime | cut -f1 -d " " | sed 's/\.../ /')

					CPU=$(expr $uptemps - $starttimeS)
					systime=$(date +%s)
					starttimeD=$(expr $systime - $CPU)
					STARTTIME=$(date -d "@$starttimeD" +"%Y/%m/%d %H:%M:%S")
					echo "$PID ${CPU}s $PRIO ${VSIZE}Mo $STARTTIME $starttimeD">>$dircour/f.txt
		fi
	done
	resultat=$(sort -nrk $sortcode -t" " $dircour/f.txt | cut -f1-6 -d " " | column -t -s" ")
	echo "$resultat">$dircour/f.txt
	head -$nblignes $dircour/f.txt
	rm $dircour/f.txt $dircour/source.txt
}
#              fonction info
#########################################################
info(){
echo "Systeme"
echo "Version du noyau : "
cat /proc/version
echo -n "Dernier Boot : "
date -d "$(cut -f1 -d. /proc/uptime) seconds ago" 
echo -n "Nombre d'ulisateurs connectés: "
who | wc -l
}
#					fonction getcode
#################################################################
getcode(){
	case $sortopt in
		mem)
			sortcode=4
			sortstring="quantite de memoire"
		;;
		cpu)
			sortcode=2
			sortstring="temps de fonctionnement"
		;;
		start)
			sortcode=7
			sortstring="date de lancement"
		;;
		prio)
			sortcode=3
			sortstring="priorite"
		;;
	esac
}


######################################PROGRAM(main)###############################################
info
inter=0
dircour=$PWD
dir=./
sortcode=4
sortopt="mem"
nblignes=5 #le nombre de processus et de fichiers par defaut.
while getopts :id:s:n: opt
do
	case $opt in
		i)
			inter=1
		;;
		d)
			if [ -d $OPTARG ]
			then
				dir=$OPTARG
			else
				echo "Option -d prend en argument le nom de repertoire existante.">&2
			fi
		;;
		s)
			for var in mem cpu start prio
			do
				if [ "$OPTARG" = "$var" ]
				then
					sortopt=$OPTARG
				fi
			done
		;;
		n)
			echo $OPTARG | egrep '^[0-9]+$' >/dev/null 2>&1
			if [ $? -eq 0 -a $(echo "$OPTARG" | awk '{print substr($0,1,1);exit}') != 0 ]
			then
				nblignes=$OPTARG
			else
				echo "Argument d'option -n est NaN">&2
			fi
		;;
		?)
			echo "usage: $0 [-i] [-n nblignes] [-d direction] [-s critere]">&2
			exit 1
		;;
	esac
done
getcode
affichage_proc
affichage_fichier
if [ $inter -eq 1 ]
then
        mod_interactif
fi
exit 0
