# Szpital

Zadanie na I projekt przedmiotu IPP 2016.

##### Krótka rzecz o kodzie
W kodzie wykorzystane są dwa tricki, dzięki którym kod jest czytelniejszy, choć mogą one wymagać krótkiego objaśnienia

###### Przestrzenie nazw
W języku C nie ma jako takich przestrzeni nazw, ale możne je zasymulować za pomocą struktur. Taka struktura zawiera w sobie wskaźniki na funkcje tej "przestrzeni", np:

    struct referencedStrings {
        ReferencedString* (*new)(char const* string);
        void (*free)(ReferencedString*);
    };
    
  W pliku nagłówkowym znajduje się wtedy również definicja zmiennej globalnej typu tej strktury, która służy jako "akcesor" do naszej przestrzeni.
  
      const struct referencedStrings ReferencedStrings;

W pliku implementacji danego modułu należy tę zmienną zainicializować konkretnymi funkcjami, które najlepiej zdefiniować jako "static", dzięki czemu mamy pewność, że tylko w tym jednym pliku będzie do nich dostęp:

    static ReferencedString* newReferencedString(char const* string);

    const struct referencedStrings ReferencedStrings = {
        .new = newReferencedString,
        .free = freeReferencedString,
    }
    
  Aby skorzystać z naszej przestrzeni nazw w innym pliku wystarczy załączyć nagłówek i używać funkcji za pomocą struktury `ReferencedStrings`
  
      ReferencedString* string = ReferencedStrings.new("testowy string");
      ReferencedStrings.free(string);
      
###### Implementacja dziedziczenia w C
Parser jest całkowicie niezależny od wszystkich innych stuktur użytych w projekcie. W żadnym miejscu Parser nie polega na znajomości strktury `Hospital`, `Patient`, `Disease`, `PatientList` czy `DiseaseList`. Modułowa implementacja Parsera jest możliwa dzięki wykorzystaniu wzorca obserwator. Implementacja obserwatora we wszystkich językach obiektowych korzysta z dziedziczenia, jednak można to zasymulować również w nieobiektowym C. Wyjaśnię to na przykładzie.

W uproszczeniu klasa to po prostu struktura (`struct`) z funkcjami, nic nie stoi na przeszkodzie, aby struktura w C miała w sobie funkcje (a właściwie - wskaźniki na funkcje):

    struct KlasaBazowa {
        void (*metoda)(struct KlasaBazowa* this);
    };
    
  Wystarczy przy inicjalizacji strktury ustawić ten wskaźnik na konkretną funkcję:
  
      void metoda(struct KlasaBazowa* this);
      struct KlasaBazowa* nowaKlasaBazowa() {
         struct KlasaBazowa* klasa = malloc(sizeof(struct KlasaBazowa));
         klasa->metoda = metoda;
         return klasa;
      }
      
  `KlasaBazowa` to jest nasz "interfejs" wzorca obserwator. Możemy teraz do pola `metoda` podpiąć dowolną funkcję i całą strukturę wysłać do Parsera, który będzie tę metodą wywoływał (choć nie wie (i nie musi wiedzieć) jaka tam jest teraz funkcja). Taka stuktura nie przyniesie jednak (jeszcze) żadnych korzyści, bo równie dobrze Parser mogłby po prostu pobierać wskaźnik na tę funkcję. Gdy mamy do dyspozycji dziedziczenie, klasa pochodna może trzymać dodatkowe pola i ciągle być przekazywana do innych modułów, które oczekują KlasyBazowej. Można to również zasymulować w C!
  
  Aby zasymulować dziedziczenie w C wystarczy, że w "klasie" pochodnej pierwszym polem będzie struktura `KlasaBazowa`:
  
    struct KlasaPochodna {
      struct KlasaBazowa super;
      struct Szpital* wskaznikNaSzpital;
    }
  
  Możemy teraz w "konstruktorze" ustawić funkcję klasy bazowej i wskaźnik `wskaznikNaSzpital` (a nawet wywołać "konstruktor" bazowy!):
  
    void metodaKlasyPochodnej(struct KlasaBazowa* this);
    struct KlasaPochodna* nowaKlasaPochodna(struct Szpital* szpital) {
       struct KlasaPochodna* klasa = malloc(sizeof(struct KlasaPochodna));
       klasa->super.metoda = metodaKlasyPochodnej;
       klasa->wskaznikNaSzpital = szpital;
       return klasa;
    }
    
  Pytanie: gdzie tu dziedziczenie skoro wskaźnik `struct KlasaPochodna*` nie jest kompatybilny z typem `struct KlasaBazowa*`... A może jest? W standardzie (C99: 6.7.2.1.5, http://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf) zagwarantowane jest, że w pamięci pola struktury będą w dokładnie takiej kolejności w jakiej została strktura zdefiniowana. To oznacza, że w pod adresem klasy pochodnej znajduje się również klasa bazowa, czyli możemy bezpiecznie rzutować klasę pochodną na klasę bazową:
  
    void wywolaj(struct KlasaBazowa* klasa) {
        klasa->metoda(klasa);
    }
    ...
    struct KlasaPochodna* pochodna = nowaKlasaPochodna(szpital);
    wywolaj((KlasaBazowa*)pochodna);
    
  Funkcja `wywolaj` oczywiście wywoła funkcję, która jest pod wskaźnikiem `metoda`, czyli funkcję naszej klasy pochodnej. Co więcej, `metodaKlasyPochodnej` może bezpiecznie rzutować parametr `this` na `struct KlasaPochodna*`, bo jest ona wywoływana tylko z `KlasyPochodnej` (wtedy wskaźnik `struct KlasaBazowa* this` wskazuje również na `struct KlasaPochodna*`)
  
    void metodaKlasyPochodnej(struct KlasaBazowa* super) {
      struct KlasaPochodna* this = (KlasaPochodna*)super;
      // mamy bez problemu dostęp do this->wskaznikNaSzpital
    }
  
  W tym przypadku rzutowanie jest zawsze bezpieczne, jest to zatem więc eleganckie rozwiązanie problemu. W ten sposób Parser i Hospital implementują wzorzec obserwator. 
