#ifndef GARBAGE_COLLECTOR_RANDOMOBJECT_H
#define GARBAGE_COLLECTOR_RANDOMOBJECT_H

#include <string>

class RandomObject
{
public:
    RandomObject() = default;
    explicit RandomObject(int i);
    ~RandomObject();
    [[nodiscard]] int getValue() const;

private:
    int _i = 0;
    std::string _bigStringThatTakesMemory = "Quel pur travail de fins eclairs consume\n"
                                            "Maint diamant d’imperceptible ecume,\n"
                                            "Et quelle paix semble se concevoir !\n"
                                            "Quand sur l’abime un soleil se repose,\n"
                                            "Ouvrages purs d’une eternelle cause,\n"
                                            "Le Temps scintille et le Songe est savoir.";
};


#endif //GARBAGE_COLLECTOR_RANDOMOBJECT_H
