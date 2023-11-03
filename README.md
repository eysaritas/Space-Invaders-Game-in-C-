# Space-Invaders-Game-in-C-
I coded space invaders game in C programming language . All files and images in the folder.

Oyunun Mucidi ve İçeriği

Space Invaders (スペースインベーダー Supēsu Inbēdā), Tomohiro Nishikado tarafından geliştirilen ve 1978'de yayımlanan bir arcade oyunudur.Oyunun amacı bir lazer silahı ile uzaylıları yenmektir. Türkiye'de oyunun Atari 2600 kartuşları Uzay Korsanlari adıyla piyasa sürülmüştür. (wikipedi.org/Space_Invaders)

Projenin İçeriği

Space Invaders oyun projem, SDL kütüphanesiyle oluşturulmuş olup 14 fonksiyon ve main içeriğiyle yazılmıştır. Projenin içeriği, 3 ana bileşenden oluşmuştur. Bunlar: Kullanıcının kontrol edebildiği uzay gemisi, uzay gemisinden düşmanlara atılmak üzere kullanılan mermiler ve düşman unsurlar uzaylılardır. 
Oyunun hatasız şekilde iki sonu vardır. Birinci son: Düşmanların uzay gemisine çarpması sonucu konsolda yazacak olan "Uzay gemisine dusman uzaylilar çarpti! Oyunu Kaybettiniz!" yazısıyla birlikte oyun sona erdilir. İkinci son: Kullanıcı kontrolündeki uzay gemisinin bütün düşmanları imha etmesi sonucu konsolda yazacak olan "Butun dusman uzaylilar olduruldu.Oyun kazanildi!" yazısıyla oyun sona erdirilir.


Proje İçeriğinde Yazılan Fonksiyonların Amaçları

init() : 

1- SDL kütüphanesi başlatılır .
2- SDL_CreateWindow() fonksiyonunu kullanarak oyun penceresi oluşturulur.
3- SDL_CreateRenderer() fonksiyonunu kullanarak oyunun görüntülerini işlemek için bir renderer oluşturulur.
Eğer fonksiyon "true" değeri dönerse oyun başarıyla başlatılmış demektir.

initShip() : 

1- ship.x ve ship.y değerlerini, uzay gemisinin başlangıç konumunu ekranın ortasında yer alacak şekilde hesaplar.
2- ship.width ve ship.height değerlerini, uzay gemisinin genişliğini ve yüksekliğini belirler.
3- ship.isMovingLeft ve ship.isMovingRight değerlerini başlangıçta false olarak ayarlar. Bu değerler, uzay gemisinin sola veya sağa hareket ettiğini belirtmek için kullanılır.
Yani, initShip() fonksiyonu oyun başladığında uzay gemisi objesinin başlangıç durumunu belirler.

initEnemies() :

1- startX ve startY değişkenleri kullanılarak, düşman uzaylıların ilk sıra ve sütununun başlangıç konumu belirlenir.
2- İki döngü kullanılarak, enemies matrisindeki her düşman uzaylılar için başlangıç konumları belirlenir.
3- Düşman uzaylıların  x ve y konumları, başlangıç konumları ve boşluklara göre hesaplanır.
4- Düşman uzaylıların boyut değerleri belirlenir.
5- Düşman uzaylıların isAlive değeri başlangıçta " true" olarak ayarlanır.
Yani, initEnemies() fonksiyonu oyun başladığında düşman uzaylıların başlangıç durumunu belirler.

initBullet() :

1- Mermi boyutları belirlenir.
2- bullet.isActive değerini başlangıçta false olarak ayarlar. Bu değer, mermi objesinin aktif olup olmadığını belirtir.
Yani, initBullet() fonksiyonu oyun başladığında mermi objesinin başlangıç durumunu belirler.

loadBackground() :

1- Arka plan görüntüsü yüklenmesini sağlar.
2- Yüklenen görüntüyü kontrol eder ve başarılı bir şekilde yüklenmediyse "false" değeri döndürür.
3- Görüntünün başarıyla yüklenip yüklenmediğini kontrol eder ve "true" veya "false" değeri döndürür.
Yani, loadBackground() fonksiyonu oyunun arka plan görüntüsünü yükler ve kullanıma hazır hale getirir.

renderBackground() :

1- backgroundTexture değişkenini kullanarak arka plan yüzeyini ekrana çizer.
Yani, renderBackground() fonksiyonu oyun ekranının arka planını görsel olarak oluşturur ve render eder.

moveShip() :

1- ship.isMovingLeft ve ship.isMovingRight değerlerine göre, uzay gemisinin sol veya sağ yönde hareket etmesini sağlar.
2- Uzay gemisinin ekranda belirli sınırlar içinde kalmasını sağlar.
Yani, moveShip() fonksiyonu kullanıcının girişlerine bağlı olarak uzay gemisini yatay yönde hareket ettirir ve geminin ekranda sınırlar içinde kalmasını sağlar.

moveEnemies() :

1- Düşmanların yatay konumlarını günceller. enemySpeed değeri tarafından belirlenen hızda sağa veya sola hareket ederler.
2- Düşmanlar ekranın sağ sınırına veya sol sınırına ulaştığında, yönlerini tersine çevirir ve aşağı doğru bir adım atarlar.
3- Düşmanların aşağı doğru hareket etmeleri sırasında, eğer düşmanlar uzay gemisi seviyesine ulaşırsa, oyuncunun oyunu kaybettiğini belirtir ve oyun durdurulur.
Yani, moveEnemies() fonksiyonu düşmanların yatay hareketini yönetir ve düşmanların sınırlar içinde kalmasını, yönlerini değiştirmesini ve oyuncunun oyunu kaybetmesini kontrol eder.

moveBullet() :

1- Eğer mermi aktif durumdaysa (bullet.isActive "true" ise), mermiyi yukarı doğru hareket ettirir.
2- Mermi yukarı doğru hareket ettiğinde ekranın üst sınırına ulaşması durumunda mermiyi devre dışı bırakır (bullet.isActive "false" yapar).
3- Mermi aktif değilse herhangi bir işlem yapmaz ve işlevsizdir.
Yani, moveBullet() fonksiyonu mermiyi yukarı doğru hareket ettirerek düşmanlara doğru ateş etmeyi sağlar ve mermiyi ekranın üst sınırına ulaştığında devre dışı bırakır.

fireBullet() :

1- Eğer mermi zaten aktif durumdaysa (bullet.isActive" true" ise), başka bir mermi ateşlemesine izin vermez ve herhangi bir işlem yapmaz.
2- Eğer mermi aktif değilse (bullet.isActive "false" ise), mermiyi ateşler.
3- Mermiyi ateşlerken, mermi başlangıç konumunu ayarlar. Uzay gemisinin x konumuna ve boyutlarına bağlı olarak mermiyi geminin ortasından çıkarır.
Yani, fireBullet() fonksiyonu kullanıcının girişine bağlı olarak mermiyi ateşler ve mermiyi uzay gemisinin ortasından çıkarak düşmanlara doğru hareket etmesini sağlar.

checkCollisions() :

1- Tüm düşmanlar ve mermi arasındaki çarpışmayı kontrol eder.
2- Eğer bir düşman ve mermi çarpışıyorsa, çarpışmanın gerçekleştiği düşmanın isAlive durumunu "false" yapar, yani düşmanın öldüğünü işaretler.
3- Aynı çarpışma kontrolü, tüm düşmanlar ve mermi kombinasyonları için gerçekleştirilir. Bu sayede mermi herhangi bir düşmana çarptığında, çarpışan düşmanın isAlive durumu "false" yapılır.
4- Mermi herhangi bir düşmana çarptığında, mermi deaktif hale getirilir (bullet.isActive "false" yapılır).
Yani, checkCollisions() fonksiyonu mermi ve düşmanlar arasındaki çarpışmaları kontrol eder ve çarpışma durumunda gerekli işlemleri gerçekleştirir. 

checkGameStatus() :

1- Tüm düşmanların durumunu kontrol eder. Eğer tüm düşmanlar öldüyse (isAlive durumu "false"), oyunun kazanıldığını belirtir.
2- Tüm düşmanlar kontrol edilirken, hala hayatta olan bir düşman bulunursa (isAlive durumu "true"), oyunun devam ettiği anlaşılır ve kontrol işlemi sonlanır.
3- Eğer tüm düşmanlar öldüyse, oyunun kazanıldığına dair bir mesaj yazdırır ve isRunning değişkenini "false" yapar, böylece oyun döngüsü sona erer.
Yani, checkGameStatus() fonksiyonu düşmanların durumunu kontrol ederek oyunun kazanılıp kazanılmadığını belirler. Eğer tüm düşmanlar öldüyse, oyuncu oyunu kazanmış olur ve oyun durdurulur. Eğer hala hayatta olan düşmanlar varsa, oyun devam eder.

gameLoop() :

1-Oyun döngüsünün sürekli olarak çalışmasını sağlar. Oyun döngüsü, oyunun devam ettiği sürece işlemlerin tekrarlanmasını sağlar.
2- SDL olaylarını yakalar ve işler. Oyuncu etkileşimlerini (klavye veya fare) algılayarak uygun eylemleri gerçekleştirir.
3- Gemiyi hareket ettirir. Gemiyi sol veya sağ yönde hareket ettirmek için moveShip() fonksiyonunu çağırır.
4- Mermiyi hareket ettirir. Mermi aktifse yukarı doğru hareket ettirilir. Mermi sınırı geçtiğinde veya bir düşmana çarptığında durdurulur.
5- Düşmanları hareket ettirir. Düşmanların yatay hareketini ve sınırlara ulaşınca aşağı inmelerini kontrol eder.
6- Çarpışma kontrollerini gerçekleştirir. Mermi ile düşman arasında çarpışma kontrolü yapar ve çarpışma durumunda düşmanı yok eder.
7- Oyun durumunu kontrol eder. Tüm düşmanlar öldüyse oyunu kazanıldı olarak işaretler ve oyun döngüsünü sonlandırır.
8- Render işlemlerini gerçekleştirir. Arka planı, gemiyi, mermiyi ve düşmanları ekrana render eder.
Yani, gameLoop() fonksiyonu oyunun ana döngüsünü oluşturarak, oyunun sürekli olarak güncellenmesini, kullanıcı etkileşimlerini takip etmesini, nesnelerin hareketini ve çarpışmaları kontrol etmesini sağlar.

close() :
1- SDL_DestroyTexture() fonksiyonunu kullanarak arka plan texture'ını serbest bırakır.
2- SDL_DestroyRenderer() fonksiyonunu kullanarak renderer'ı serbest bırakır.
3- SDL_DestroyWindow() fonksiyonunu kullanarak oyun penceresini serbest bırakır.
4- SDL_Quit() fonksiyonunu kullanarak SDL kütüphanesini kapatır.
Yani, close() fonksiyonu oyunun sonlandırılması ve kullanılan kaynakların temizlenmesi işlemlerini gerçekleştirir.


