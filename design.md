## Design :

### 1)	Principe de la mise en �uvre de la solution
Nous avois choisis d�utiliser comme langage de programmation le C++ qui est l�un des plus adapt� pour la programmation d�application OpenGL. 
De plus, comme l�id�e dans ce projet �tait principalement de d�couvrir le fonctionnement d�OpenGL et de la mod�lisation 3D nous avons choisis d�utiliser le moins possible les biblioth�ques d�j� existantes. 
Nous utilisons donc : 
Glew : Une biblioth�que qui permet une gestion simple des extensions OpenGL.
GLFW : Une biblioth�que qui permet la gestion de fen�tres OpenGL.
GLM : Une biblioth�que math�matique qui permet entre autres la gestion de matrices, vecteurs.
STBI : Une biblioth�que qui permet de parser et d�compresser des fichiers images.
FASTNOISE : Une biblioth�que qui permet la g�n�ration de bruit
Ces biblioth�ques nous semblaient n�cessaires car elles nous facilitent la gestion de certains, qui auraient pu �tre tr�s chronophage, sans �tre vraiment pertinent dans notre projet.

### 2)	R�gles d�architectures 
Notre solution se compose en trois niveaux d�abstraction : 
Les plus basses sont les classes qui permettent de faire le lien entre notre application et la carte graphique : 
-	VertexBuffer : Permet de cr�er un buffer pour envoyer des �vertices� � la carte graphique.
-	IndexBuffer : M�me principe que VertexBuffer mais pour des indices.
-	VertexBufferLayout : Pour s�parer les diff�rentes donn�es comprises dans un vertex, un vertex pouvant avoir jusqu�� trois types de donn�es en m�me temps, des coordonn�es dans l�espace, des coordonn�es pour les textures, 
	et des coordonn�es pour les normales. Cette classe permet de dire � OpenGL de quel type de donn�e il s�agit. 
-	VertexArray : Permet de lier une instance de VertexBuffer avec une instance de VertexBufferLayout.
-	Shader : Permet de r�cup�rer un fichier txt pour g�n�rer le code GLSL (langage de programmation des shader pour OpenGL) qui sert � programmer les shaders (ils calculent la couleur de chaque pixel � afficher).
-	Texture : Permet d�ouvrir un fichier image (png, dds, jpg...) de cr�er une texture OpenGL et d�envoyer � la carte graphique les diff�rentes donn�es associ�es � cette image.
Chacune de ces classes poss�dent des m�thodes Bind/Unbind qui permettent de lier l�instance de la classe � la carte graphique pour pouvoir les utiliser � n�importe quel moment, et de s�y d�tacher une fois qu�on en a plus besoin.


Viennent ensuite deux autres classes : 
-	La classe Mesh : contient la liste des �vertices�, informations de chaque point du mod�le, et la liste des �indices� qui d�termine l�ordre dans lequel afficher chaque point.
-	La classe Materials : contient les informations des diff�rents shaders et textures. 

Puis le dernier niveau, qui contient les classes Objects, Terrain, Cloud, qui utilisent les classes Mesh et Material pour d�finir des objects plus complexe, ayant une forme et un ou plusieurs mat�riaux.

Il y�a en plus deux autres classes: 
-	Camera : qui permet � l�utilisateur de se d�placer dans l�espace, et de pouvoir utiliser certaines macros.
-	Renderer : qui permet d�afficher les diff�rents mod�les � l��cran.

### 3)	Mod�le dynamique
Une fois les diff�rents assets (objets, terrain�) charg�s, on entre dans une boucle qui permet d�afficher tous ces �l�ments.
Mais � chaque frame, avant de les afficher il faut d�terminer leurs nouvelles positions, car lorsque l�utilisateur d�place la cam�ra c�est en fait tout le monde autour qui se d�place et la cam�ra qui reste fixe. 
Il faut donc appliquer � chaque objet � afficher un d�placement en fonction des mouvements fait par l�utilisateur.
De plus, comme dis plus haut, on a d�fini quelque macro sur le clavier on peut par exemple, avec les touches E et R changer le mode d�affichage :
	E permet d�afficher uniquement les lignes qui relie chaque vertex alors que R est l�affichage plein. 
	On peut aussi, par exemple, quitter le mode FPS, pour utiliser la souris sans faire bouger la cam�ra avec J et y revenir avec ESPACE. 

### 4)	Contraintes
La principale difficult� pour nous a �t� de devoir apprendre et comprendre le fonctionnement d'OpenGL et de faire l�application en m�me temps. 
A chaque grande partie il a fallu se documenter pour comprendre comme �a fonctionne puis r�ussir � en faire quelque chose de fonctionnel pouvant �tre int�grer dans notre solution.
L�autre grande contrainte a �t� de devoir rendre cette solution multi-plateforme. 
En effet, certains travaillaient sur Linux, d�autres sur Windows, nous avons aussi du faire fonctionner notre solution sur Mac. 
On est donc quelques fois tomb� sur des fonctions n�cessaires, mais qui n�existaient que sur Linux ou sur windows. 
Pour pallier � ce probl�me il nous a suffi de cr�er un fichier ayant le m�me nom pour linux et windows, avec le contenu adapt�, que l�on ne push pas sur Github. 
Ainsi le code avait toujours le m�me include quel que soit la plateforme, mais son contenu �t� diff�rent. 
Il a aussi fallu s�adapter � Github, pour la plupart d�entre nous c��tait la premi�re que nous l�utilisions et ce n�est pas simple d�int�grer tout le fonctionnement au d�but.

### 5)	Cadre de production  
Pour la production de ce projet nous avons donc utiliser diff�rents logiciels, sur windows nous �tions sur VisualStudio et sur Linux nous utilisions VIM, en utilisant Make, gdb et GCC, pour compiler et d�boguer le programme.
