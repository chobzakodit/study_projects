#                      _..._                 .           __.....__
#                    .'     '.             .'|       .-''         '.
#                   .   .-.   .          .'  |      /     .-''"'-.  `.
#                   |  '   '  |    __   <    |     /     /________\   \
#               _   |  |   |  | .:--.'.  |   | ____|                  |
#             .' |  |  |   |  |/ |   \ | |   | \ .'\    .-------------'
#            .   | /|  |   |  |`" __ | | |   |/  .  \    '-.____...---.
#          .'.'| |//|  |   |  | .'.''| | |    /\  \  `.             .'
#        .'.'.-'  / |  |   |  |/ /   | |_|   |  \  \   `''-...... -'
#        .'   \_.'  |  |   |  |\ \._,\ '/'    \  \  \
#                   '--'   '--' `--'  `"'------'  '---'
#
#
#
#                                               .......
#                                     ..  ...';:ccc::,;,'.
#                                 ..'':cc;;;::::;;:::,'',,,.
#                              .:;c,'clkkxdlol::l;,.......',,
#                          ::;;cok0Ox00xdl:''..;'..........';;
#                          o0lcddxoloc'.,. .;,,'.............,'
#                           ,'.,cc'..  .;..;o,.       .......''.
#                             :  ;     lccxl'          .......'.
#                             .  .    oooo,.            ......',.
#                                    cdl;'.             .......,.
#                                 .;dl,..                ......,,
#                                 ;,.                   .......,;
#                                                        ......',
#                                                       .......,;
#                                                       ......';'
#                                                      .......,:.
#                                                     .......';,
#                                                   ........';:
#                                                 ........',;:.
#                                             ..'.......',;::.
#                                         ..';;,'......',:c:.
#                                       .;lcc:;'.....',:c:.
#                                     .coooc;,.....,;:c;.
#                                   .:ddol,....',;:;,.
#                                  'cddl:'...,;:'.
#                                 ,odoc;..',;;.                    ,.
#                                ,odo:,..';:.                     .;
#                               'ldo:,..';'                       .;.
#                              .cxxl,'.';,                        .;'
#                              ,odl;'.',c.                         ;,.
#                              :odc'..,;;                          .;,'
#                              coo:'.',:,                           ';,'
#                              lll:...';,                            ,,''
#                              :lo:'...,;         ...''''.....       .;,''
#                              ,ooc;'..','..';:ccccccccccc::;;;.      .;''.
#          .;clooc:;:;''.......,lll:,....,:::;;,,''.....''..',,;,'     ,;',
#       .:oolc:::c:;::cllclcl::;cllc:'....';;,''...........',,;,',,    .;''.
#      .:ooc;''''''''''''''''''',cccc:'......'',,,,,,,,,,;;;;;;'',:.   .;''.
#      ;:oxoc:,'''............''';::::;'''''........'''',,,'...',,:.   .;,',
#     .'';loolcc::::c:::::;;;;;,;::;;::;,;;,,,,,''''...........',;c.   ';,':
#     .'..',;;::,,,,;,'',,,;;;;;;,;,,','''...,,'''',,,''........';l.  .;,.';
#    .,,'.............,;::::,'''...................',,,;,.........'...''..;;
#   ;c;',,'........,:cc:;'........................''',,,'....','..',::...'c'
#  ':od;'.......':lc;,'................''''''''''''''....',,:;,'..',cl'.':o.
#  :;;cclc:,;;:::;''................................'',;;:c:;,'...';cc'';c,
#  ;'''',;;;;,,'............''...........',,,'',,,;:::c::;;'.....',cl;';:.
#  .'....................'............',;;::::;;:::;;;;,'.......';loc.'.
#   '.................''.............'',,,,,,,,,'''''.........',:ll.
#    .'........''''''.   ..................................',;;:;.
#      ...''''....          ..........................'',,;;:;.
#                                ....''''''''''''''',,;;:,'.
#                                    ......'',,'','''..
#


################################################################################
#                  Fonctions d'affichage et d'entrée clavier                   #
################################################################################

# Ces fonctions s'occupent de l'affichage et des entrées clavier.
# Il n'est pas obligatoire de comprendre ce qu'elles font.

.data

# Tampon d'affichage du jeu 256*256 de manière linéaire.

frameBuffer: .word 0 : 1024  # Frame buffer

# Code couleur pour l'affichage
# Codage des couleurs 0xwwxxyyzz où
#   ww = 00
#   00 <= xx <= ff est la couleur rouge en hexadécimal
#   00 <= yy <= ff est la couleur verte en hexadécimal
#   00 <= zz <= ff est la couleur bleue en hexadécimal

colors: .word 0x00000000, 0x00ff0000, 0xff00ff00, 0x00396239, 0x00ff00ff, 0x000066cc, 0x00cc6611, 0x00463349, 0x00ffe28a 
.eqv black 0
.eqv red   4
.eqv green 8
.eqv greenV2  12
.eqv rose  16
.eqv blue 20
.eqv orange 24
.eqv violet 28
.eqv jaune 32
# Dernière position connue de la queue du serpent.

lastSnakePiece: .word 0, 0

.text
j main

############################# printColorAtPosition #############################
# Paramètres: $a0 La valeur de la couleur
#             $a1 La position en X
#             $a2 La position en Y
# Retour: Aucun
# Effet de bord: Modifie l'affichage du jeu
################################################################################

printColorAtPosition:
lw $t0 tailleGrille
mul $t0 $a1 $t0
add $t0 $t0 $a2
sll $t0 $t0 2
sw $a0 frameBuffer($t0)
jr $ra

################################ resetAffichage ################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Réinitialise tout l'affichage avec la couleur noir
################################################################################

resetAffichage:
lw $t1 tailleGrille
mul $t1 $t1 $t1
sll $t1 $t1 2
la $t0 frameBuffer
addu $t1 $t0 $t1
lw $t3 colors + black

RALoop2: bge $t0 $t1 endRALoop2
  sw $t3 0($t0)
  add $t0 $t0 4
  j RALoop2
endRALoop2:
jr $ra

################################## printSnake ##################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Change la couleur de l'affichage aux emplacement ou se
#                trouve le serpent et sauvegarde la dernière position connue de
#                la queue du serpent.
################################################################################

printSnake:
subu $sp $sp 12
sw $ra 0($sp)
sw $s0 4($sp)
sw $s1 8($sp)

lw $s0 tailleSnake
sll $s0 $s0 2
li $s1 0

lw $a0 colors + green
lw $a1 snakePosX($s1)
lw $a2 snakePosY($s1)
jal printColorAtPosition
li $s1 4

PSLoop:
bge $s1 $s0 endPSLoop #s0=4 s1=====0 =>s0=8 =>s0=12
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
beq $a0 0x00463349 BLUE  #463348=violet
beq $a0 0x000066cc GREENV2  #0066cc=blue
beq $a0 0x00396239 JAUNE    #396239=greenV2
beq $a0 0x00cc6611 RED    #cc6611=orange
beq $a0 0x00ffe28a ORANGE    #ffe28a=jaune
beq $a0 0x00ff0000 VIOLET
VIOLET:
  lw $a0 colors + violet
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
RED:
  lw $a0 colors + red
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
BLUE:
  lw $a0 colors + blue
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
ORANGE:
  lw $a0 colors + orange
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
GREENV2:
  lw $a0 colors + greenV2
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
JAUNE:
  lw $a0 colors + jaune
  lw $a1 snakePosX($s1)
  lw $a2 snakePosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j PSLoop
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  

endPSLoop:

subu $s0 $s0 4
lw $t0 snakePosX($s0)
lw $t1 snakePosY($s0)
sw $t0 lastSnakePiece
sw $t1 lastSnakePiece + 4

lw $s1 8($sp)
lw $s0 4($sp)
lw $ra 0($sp)
addu $sp $sp 12
jr $ra

################################ printObstacles ################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Change la couleur de l'affichage aux emplacement des obstacles.
################################################################################

printObstacles:
subu $sp $sp 12
sw $ra 0($sp)
sw $s0 4($sp)
sw $s1 8($sp)

lw $s0 numObstacles
sll $s0 $s0 2
li $s1 0

POLoop:
bge $s1 $s0 endPOLoop
  lw $a0 colors + red
  lw $a1 obstaclesPosX($s1)
  lw $a2 obstaclesPosY($s1)
  jal printColorAtPosition
  addu $s1 $s1 4
  j POLoop
endPOLoop:

lw $ra 0($sp)
lw $s0 4($sp)
lw $s1 8($sp)
addu $sp $sp 12
jr $ra

################################## printCandy ##################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Change la couleur de l'affichage à l'emplacement du bonbon.
################################################################################

printCandy:
subu $sp $sp 4
sw $ra ($sp)

lw $a0 colors + rose
lw $a1 candy
lw $a2 candy + 4
jal printColorAtPosition

lw $ra ($sp)
addu $sp $sp 4
jr $ra

eraseLastSnakePiece:
subu $sp $sp 4
sw $ra ($sp)

lw $a0 colors + black
lw $a1 lastSnakePiece
lw $a2 lastSnakePiece + 4
jal printColorAtPosition

lw $ra ($sp)
addu $sp $sp 4
jr $ra

################################## printGame ###################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Effectue l'affichage de la totalité des éléments du jeu.
################################################################################

printGame:
subu $sp $sp 4
sw $ra 0($sp)

jal eraseLastSnakePiece
jal printSnake
jal printObstacles
jal printCandy

lw $ra 0($sp)
addu $sp $sp 4
jr $ra

############################## getRandomExcluding ##############################
# Paramètres: $a0 Un entier x | 0 <= x < tailleGrille
# Retour: $v0 Un entier y | 0 <= y < tailleGrille, y != x
################################################################################

getRandomExcluding:
move $t0 $a0
lw $a1 tailleGrille
li $v0 42
syscall
beq $t0 $a0 getRandomExcluding
move $v0 $a0
jr $ra

########################### newRandomObjectPosition ############################
# Description: Renvoie une position aléatoire sur un emplacement non utilisé
#              qui ne se trouve pas devant le serpent.
# Paramètres: Aucun
# Retour: $v0 Position X du nouvel objet
#         $v1 Position Y du nouvel objet
################################################################################

newRandomObjectPosition:
subu $sp $sp 4
sw $ra ($sp)

lw $t0 snakeDir
and $t0 0x1
bgtz $t0 horizontalMoving
li $v0 42
lw $a1 tailleGrille
syscall
move $t8 $a0
lw $a0 snakePosY
jal getRandomExcluding
move $t9 $v0
j endROPdir

horizontalMoving:
lw $a0 snakePosX
jal getRandomExcluding
move $t8 $v0
lw $a1 tailleGrille
li $v0 42
syscall
move $t9 $a0
endROPdir:

lw $t0 tailleSnake
sll $t0 $t0 2
la $t0 snakePosX($t0)
la $t1 snakePosX
la $t2 snakePosY
li $t4 0

ROPtestPos:
bge $t1 $t0 endROPtestPos
lw $t3 ($t1)
bne $t3 $t8 ROPtestPos2
lw $t3 ($t2)
beq $t3 $t9 replayROP
ROPtestPos2:
addu $t1 $t1 4
addu $t2 $t2 4
j ROPtestPos
endROPtestPos:

bnez $t4 endROP

lw $t0 numObstacles
sll $t0 $t0 2
la $t0 obstaclesPosX($t0)
la $t1 obstaclesPosX
la $t2 obstaclesPosY
li $t4 1
j ROPtestPos

endROP:
move $v0 $t8
move $v1 $t9
lw $ra ($sp)
addu $sp $sp 4
jr $ra

replayROP:
lw $ra ($sp)
addu $sp $sp 4
j newRandomObjectPosition

################################# getInputVal ##################################
# Paramètres: Aucun
# Retour: $v0 La valeur 0 (haut), 1 (droite), 2 (bas), 3 (gauche), 4 erreur
################################################################################

getInputVal:
lw $t0 0xffff0004
li $t1 115
beq $t0 $t1 GIhaut
li $t1 122
beq $t0 $t1 GIbas
li $t1 113
beq $t0 $t1 GIgauche
li $t1 100
beq $t0 $t1 GIdroite
li $v0 4
j GIend

GIhaut:
li $v0 0
j GIend

GIdroite:
li $v0 1
j GIend

GIbas:
li $v0 2
j GIend

GIgauche:
li $v0 3

GIend:
jr $ra

################################ sleepMillisec #################################
# Paramètres: $a0 Le temps en milli-secondes qu'il faut passer dans cette
#             fonction (approximatif)
# Retour: Aucun
################################################################################

sleepMillisec:
move $t0 $a0
li $v0 30
syscall
addu $t0 $t0 $a0

SMloop:
bgt $a0 $t0 endSMloop
li $v0 30
syscall
j SMloop

endSMloop:
jr $ra

##################################### main #####################################
# Description: Boucle principal du jeu
# Paramètres: Aucun
# Retour: Aucun
################################################################################

main:

# Initialisation du jeu

jal resetAffichage
jal newRandomObjectPosition
sw $v0 candy
sw $v1 candy + 4


# Boucle de jeu

mainloop:

jal getInputVal
move $a0 $v0
jal majDirection
jal updateGameStatus
jal conditionFinJeu
bnez $v0 gameOver
jal printGame
lw $a0 vitesse
jal sleepMillisec
j mainloop

gameOver:
jal affichageFinJeu
li $v0 10
syscall

################################################################################
#                                Partie Projet                                 #
################################################################################

# À vous de jouer !

.data

tailleGrille:  .word 16        # Nombre de case du jeu dans une dimension.

# La tête du serpent se trouve à (snakePosX[0], snakePosY[0]) et la queue à
# (snakePosX[tailleSnake - 1], snakePosY[tailleSnake - 1])
tailleSnake:   .word 1         # Taille actuelle du serpent.
snakePosX:     .word 0 : 1024  # Coordonnées X du serpent ordonné de la tête à la queue.
snakePosY:     .word 0 : 1024  # Coordonnées Y du serpent ordonné de la t.

# Les directions sont représentés sous forme d'entier allant de 0 à 3:
snakeDir:      .word 1         ## Direction du serpent: 0 (haut), 1 (droite)
                               #                        2 (bas),  3 (gauche)
numObstacles:  .word 0         # Nombre actuel d'obstacle présent dans le jeu.
obstaclesPosX: .word 0 : 1024  # Coordonnées X des obstacles
obstaclesPosY: .word 0 : 1024  # Coordonnées Y des obstacles
candy:         .word 0, 0      # Position du bonbon (X,Y)
scoreJeu:      .word 0         # Score obtenu par le joueur



#	BONUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
affichescore: .asciiz "Vous etes mort, mon amigo!, Votre Score est:"
vitesse: .word 500
#         BONUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
.text

################################# majDirection #################################
# Paramètres: $a0 La nouvelle position demandée par l'utilisateur. La valeur
#                 étant le retour de la fonction getInputVal.
# Retour: Aucun
# Effet de bord: La direction du serpent à été mise à jour.
# Post-condition: La valeur du serpent reste intacte si une commande illégale
#                 est demandée, i.e. le serpent ne peut pas faire de demi-tour
#                 en un unique tour de jeu. Cela s'apparente à du cannibalisme
#                 et à été proscrit par la loi dans les sociétés reptiliennes.
################################################################################

majDirection:
# En haut, ... en bas, ... à gauche, ... à droite, ... ces soirées là ...
lw $t0 snakeDir
beq $t0 $a0 FinDir
li $t1 0
beq $a0 $t1 VerifHaut
li $t1 1
beq $a0 $t1 VerifDroite
li $t1 2
beq $a0 $t1 VerifBas
li $t1 3
beq $a0 $t1 VerifGauche
j FinDir

VerifHaut:
li $t2 2
beq $t0 $t2 FinDir
sw $a0 snakeDir
j FinDir

VerifDroite:
li $t2 3
beq $t0 $t2 FinDir
sw $a0 snakeDir
j FinDir

VerifBas:
li $t2 0
beq $t0 $t2 FinDir
sw $a0 snakeDir
j FinDir

VerifGauche:
li $t2 1
beq $t0 $t2 FinDir
sw $a0 snakeDir
j FinDir

FinDir:
jr $ra

############################### updateGameStatus ###############################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: L'état du jeu est mis à jour d'un pas de temps. Il faut donc :
#                  - Faire bouger le serpent
#                  - Tester si le serpent à manger le bonbon
#                    - Si oui déplacer le bonbon et ajouter un nouvel obstacle
################################################################################

updateGameStatus:
subu $sp $sp 4
sw $ra 0($sp)
# jal hiddenCheatFunctionDoingEverythingTheProjectDemandsWithoutHavingToWorkOnIt
MoveCorps:#decalage tableau ---- faire des copies de chaque element precedent
lw $t0 tailleSnake
li $t1 2
Boucle:blt $t0 $t1 MoveTete
#ne pas changer $t0 et $t1 sauf ligne avant-dernierde la boucle!!!
subi $t2 $t0 1# offset element destination
subi $t3 $t0 2# offset element source
li $t5 4
mul $t2 $t2 $t5#   t2=offset en octete d'adresse element destination
mul $t3 $t3 $t5#   t3=offset en octete d'adresse d'element source
lw $t4 snakePosX($t3)#    element source-copie
sw $t4 snakePosX($t2)# 	  charger cette copie dans element-destination
#de meme pour Y
lw $t4 snakePosY($t3)
sw $t4 snakePosY($t2)
subi $t0 $t0 1	     #	  decrementation - continuer le boucle
j Boucle


MoveTete:	#Claire sans explication...MAIS POURQUOI X EN BAS??
lw $t0 snakeDir
li $t1 0
beq $t0 $t1 MoveHaut
li $t1 1
beq $t0 $t1 MoveDroite
li $t1 2
beq $t0 $t1 MoveBas
li $t1 3
beq $t0 $t1 MoveGauche
j FinMove

MoveHaut:
lw $t2 snakePosX
addi $t2 $t2 1
sw $t2 snakePosX
j FinMove

MoveDroite:
lw $t2 snakePosY
addi $t2 $t2 1
sw $t2 snakePosY
j FinMove

MoveBas:
lw $t2 snakePosX
subi $t2 $t2 1
sw $t2 snakePosX
j FinMove

MoveGauche:
lw $t2 snakePosY
subi $t2 $t2 1
sw $t2 snakePosY
j FinMove

FinMove:

#test de nourriture
lw $t1 candy     #PosX
lw $t2 candy + 4 #PosY
lw $t3 snakePosX
lw $t4 snakePosY
bne $t1 $t3 FinUpdate
bne $t2 $t4 FinUpdate
#augmente taille snake
lw $t0 tailleSnake # t0=taille ancienne

InsertTail:
subi $t1 $t0 1# offset de dernier element
li $t2 4
mul $t1 $t1 $t2#   t1=offset en OCTETE d'adresse de dernier element
mul $t2 $t0 $t2#   t2=offset en OCTETE d'adresse de nouveau element
lw $t3 snakePosX($t1)#    t3=dernier element-copie
sw $t3 snakePosX($t2)# 	  charger cette copie dans nouveau element
#de meme pour Y
lw $t3 snakePosY($t1)
sw $t3 snakePosY($t2)

addi $t0 $t0 1 #t0=t0+1        taille neuf
sw $t0 tailleSnake

lw $t0 scoreJeu	
addi $t0 $t0 1	#score+1 pour chaque candy
sw $t0 scoreJeu

jal newRandomObjectPosition
sw $v0 candy # posx
sw $v1 candy + 4 #posy

jal newRandomObjectPosition#les memes chose mais avec obstaclesPos*
lw $t0 numObstacles
li $t1 4
mul $t1 $t1 $t0
sw $v0 obstaclesPosX($t1)
sw $v1 obstaclesPosY($t1)
addi $t0 $t0 1
sw $t0 numObstacles
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUS!!!!!!!!!!!!!!!!!!!!!!
lw $t0 vitesse
subu $t0 $t0 10
sw $t0 vitesse
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BONUS!!!!!!!!!!!!!!!!!!!!!!
j FinUpdate

FinUpdate:
lw $ra 0($sp)
addi $sp $sp 4
jr $ra

############################### conditionFinJeu ################################
# Paramètres: Aucun
# Retour: $v0 La valeur 0 si le jeu doit continuer ou toute autre valeur sinon.
################################################################################

conditionFinJeu:

Frontiere:	#pourque serpent etait dans une boite
lw $t0 snakePosX
lw $t1 snakePosY
li $t2 15
blt $t0 $zero MauvaisFin
bgt $t0 $t2 MauvaisFin
blt $t1 $zero MauvaisFin
bgt $t1 $t2 MauvaisFin

RdvObstacles:	#Le nom dit tout
lw $t4 numObstacles
li $t5 0
li $t6 4
ObstBoucle:beq $t5 $t4 RdvQueue	#boucle - pour verifier tous les obstacles (il faut traverser tout le tableau)
mul $t7 $t5 $t6
addi $t5 $t5 1
lw $t2 obstaclesPosX($t7)
lw $t3 obstaclesPosY($t7)
bne $t0 $t2 ObstBoucle
bne $t1 $t3 ObstBoucle
j MauvaisFin

RdvQueue:	#la meme chose
lw $t4 tailleSnake
li $t5 4	# 4 - parce que seulement a partir de taille=5 le serpent peut se "manger"
li $t6 4	#pour multiplier
QueueBoucle:bge $t5 $t4 BonFin
mul $t7 $t5 $t6
addi $t5 $t5 1
lw $t2 snakePosX($t7)
lw $t3 snakePosY($t7)
bne $t0 $t2 QueueBoucle
bne $t1 $t3 QueueBoucle
j MauvaisFin

BonFin:
li $v0 0
jr $ra

MauvaisFin:
li $v0 1
jr $ra

############################### affichageFinJeu ################################
# Paramètres: Aucun
# Retour: Aucun
# Effet de bord: Affiche le score du joueur dans le terminal suivi d'un petit
#                mot gentil (Exemple : «Quelle pitoyable prestation !»).
# Bonus: Afficher le score en surimpression du jeu.
################################################################################

affichageFinJeu:

# Fin.
li $v0 56
la $a0 affichescore
lw $a1 scoreJeu
syscall
jr $ra
