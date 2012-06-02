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

mkdir $name 2> /dev/null

if [ $? -ne 0 ];then
	echo "Skin déjà existant."
	exit 1
fi

cp -R ./default/* "$name/"

cd $name

echo "Titre du skin : "
read title

echo "\nChargement des images. Si vous souhaitez garder certaines images par défaut laissez les champs vides.\n"

echo "Chemin du background : "
read path

if [ -z $path ];then
	cp ../default/mback.png .
else
	if [ -f $path ];then
		continue
	else
		echo "Le fichier n'existe pas."
		exit 1
	fi
	filename=$(basename $path)
	ext=${filename##*.}

	if [ $ext != "png" ];then
		echo "Mauvais format de fichier."
		exit 1
	fi
	cp "$path" ./mback.png
fi

for i in $(seq 1 4)
do

	echo "Chemin avatar joueur $i : "
	read avatar
		
	if [ -z $avatar ];then
		cp ../default/player"$i".png .
	else
		if [ -f $avatar ];then
			continue
		else
			echo "Le fichier n'existe pas."
			exit 1
		fi
		filename=$(basename $avatar)
		ext=${avatar##*.}

		if [ $ext != "png" ];then
			echo "Mauvais format de fichier."
			exit 1
		fi
		cp "$avatar" "./player$i.png"
	fi
done

touch colors.conf

echo "Configuration des codes couleurs"
echo "Pour chaque paramètre, veuillez saisir les composantes RGB\n"

echo "\nbackground => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "bg.R: $r\nbg.G: $g\nbg.B: $b" >> colors.conf

echo "\nlink => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "link.R: $r\nlink.G: $g\nlink.B: $b" >> colors.conf

echo "\nerror => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "error.R: $r\nerror.G: $g\nerror.B: $b" >> colors.conf

echo "\nselected => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "selected.R: $r\nselected.G: $g\nselected.B: $b" >> colors.conf

echo "\nselectedbg => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "selectedbg.R: $r\nselectedbg.G: $g\nselectedbg.B: $b" >> colors.conf

echo "\ntitle => \n"
echo "R ?"
read r
while [ $r -lt 0 ] || [ $r -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n R ?"
	read r
done
echo "G ?"
read g
while [ $g -lt 0 ] || [ $g -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n G ?"
	read g
done
echo "B ?"
read b
while [ $b -lt 0 ] || [ $b -gt 255 ];do
	echo "Veuillez saisir une valeur comprise entre 0 et 255.\n B ?"
	read r
done
echo "title.R: $r\ntitle.G: $g\ntitle.B: $b" >> colors.conf

echo "$name:$title" >> ../skins.conf

echo "\n\nLa création de votre skin s'est terminée avec succès.\n"



