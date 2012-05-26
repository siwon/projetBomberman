#!/bin/bash

# Script de création de skin PolyBomber
# Author : Alexandre BISIAUX


cd ./resources/skins/

echo  " _____   _____         __   __ ______   _____  _______ ______  _______  ______
 |_____] |     | |        \_/   |_____] |     | |  |  | |_____] |______ |_____/
 |       |_____| |_____    |    |_____] |_____| |  |  | |_____] |______ |    \_"
 
echo "\n\n		Utilitaire de creation de skin"

echo "\n\nVeuillez lire le manuel d'utilisation afin de créer les différents fichiers nécessaires.\n\n"

echo "Nom du skin : "
read name

echo "Titre du skin : "
read title

echo "Chemin du background : "
read path

mkdir $name 2> /dev/null

if [ $? -ne 0 ];then
	echo "Skin déjà existant."
	exit 1
fi

if [ -f $path ];then
	continue
else
	echo "Le fichier n'existe pas."
	exit 1
fi

cp ./default/mback.png "$name/"
cp ./default/splash.png "$name/"
cp ./default/wiiScreen.png "$name/"

cd $name

filename=$(basename $path)
ext=${filename##*.}

if [ $ext != "png" ];then
	echo "Mauvais format de fichier."
	exit 1
fi

cp "$path" "./mback.png"

touch colors.conf

echo "Configuration des codes couleurs"
echo "Pour chaque paramètre, veuillez saisir les composantes RGB\n"

echo "background =>\n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "bg.R: $r\nbg.G: $g\nbg.B: $b" >> colors.conf

echo "link =>\n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "link.R: $r\nlink.G: $g\nlink.B: $b" >> colors.conf

echo "Erreur => \n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "error.R: $r\nerror.G: $g\nerror.B: $b" >> colors.conf

echo "selected => \n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "selected.R: $r\nselected.G: $g\nselected.B: $b" >> colors.conf

echo "selectedbg => \n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "selectedbg.R: $r\nselectedbg.G: $g\nselectedbg.B: $b" >> colors.conf

echo "title => \n"
echo "R ?"
read r
echo "G ?"
read g
echo "B ?"
read b
echo "title.R: $r\ntitle.G: $g\ntitle.B: $b" >> colors.conf

echo "$name:$title" >> ../skins.conf

echo "\n\nLa création de votre skin s'est terminée avec succès.\n"



