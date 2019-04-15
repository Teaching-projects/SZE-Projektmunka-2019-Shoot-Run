# SNR Manual

Fejlesztői környezet:

- Visual Studio 2017
  - QT VStools
- QT Creator 5.12.0
  - mswc-2017\_64
- Windows SDK 10

Könyvtárak:

- EasyExif ([https://github.com/mayanklahiri/easyexif](https://github.com/mayanklahiri/easyexif))
- [https://www.codesynthesis.com/products/odb/download.xhtml](https://www.codesynthesis.com/products/odb/download.xhtml)
  - db-2.4.0-i686-windows
  - libodb-2.4.0
  - libodb-mysql-2.4.0
  - libodb-qt-2.4.0
- MySQL 5.5.43 64bit RAR ([https://downloads.mysql.com/archives/community/](https://downloads.mysql.com/archives/community/?fbclid=IwAR0LnRRz072tmJwq9yfv4ECIwYn52DdjHyfLrlxMYs7X_k-E5GwPwRh1NBQ))

**Telepítési útmutató**

1. [https://github.com/Teaching-projects/SZE-Projektmunka-2019-Shoot-Run](https://github.com/Teaching-projects/SZE-Projektmunka-2019-Shoot-Run) repository klónozása
2. SNR/Project mappán belül létrehozunk egy Libraries mappát, ide kicsomagoljuk a 4 odb rar fájlt és a MySQL rart. És a kicsomagolt mappák nevét átnevezzük ezekre:
  - db
  - libodb
  - lidodb-mysql
  - libodb-qt
  - mysql
3. A libodb mappában megnyitjuk a vc12 solution fájlt és beállítjuk 64bitre és lefuttatjuk Release és Debug módban.
4. libodb-mysql
  - A libodb-mysql-ben megnyitjuk a vc12 solution fájlt
  - A projekt tulajdonságain belül az include directories-hez hozzárendeljük a libodb mappáját plusz a mysql/include mappát
  - A projekt tulajdonságain belül a libraries directories-hez hozzárendeljük a libodb/lib64 mappát plusz a mysql/lib mappát majd futtatjuk 64 bit Debug és Release módban.
5. A libodb-qt
  - A libodb-qt-ben megnyitjuk a vc12 solution fájlt.
  - A projekt tulajdonságain belül az include directories-hez hozzárendeljük a libodb mappáját plusz a QT/5.12.0/msvc2017\_64/include mappát
  - A projekt tulajdonságain belül a libraries directories-hez hozzárendeljük a libodb/lib64 mappát plusz a QT/5.12.0/msvc2017\_64/lib mappát majd futtatjuk 64 bit Debug és Release módban.
6. A Windows környezeti változóin belül a Path rendszerváltozóhoz hozzáadjuk:
  - a libodb/bin64
  - libodb-mysql/bin64
  - libodb-qt/bin64
  - mysql/lib
  - db/bin
7. Az SNR mappán belül lévő solution fájlt megnyitjuk, és ha mindent úgy csináltunk ahogy le van írva akkor le fog futni, mert már előre hozzávannak rendelve az elérési útvonalak.
