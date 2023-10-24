#include "include/Vector3.hpp"
#include "include/Vector2.hpp"

int main() {
    Vector3<int> lol = Vector3<int>(1, 2, 3);
    
    // lol.z = -5;
    std::cout << "TEst : " << lol.x << " et " << lol.y << " ett " << lol.z << "\n";

    Vector3<int> r = lol;
    
    std::cout << "TEst : " << r.data[0] << " et " << r.data[1] << " ett " << r.data[2] << "\n";

    std::cout << "TEst2 : " << r.getMatrice()[0] << " et " << r.getMatrice()[1] << " ett " << r.getMatrice()[2] << "\n";
}