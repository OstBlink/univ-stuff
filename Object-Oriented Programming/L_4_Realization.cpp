  #include <iostream>
  #include <string>
  #include <vector>

  // Base Component class
  class Component {
  public:
      Component(std::string mfr, std::string mdl, double p, std::string t) : 
          name(mfr + " " + mdl), type(t) {}
      virtual ~Component() {}
      virtual std::string getDetails() {
          return type + ": " + name;
      }
  private:
      std::string name;
      std::string type;
  };

  // Component derived classes
  class CPU : public Component {
  private:
      double clockSpeed;
      int coreCount;
      std::string socket;
  public:
      CPU(std::string mfr, std::string mdl, double p, int cores, double clock, std::string s) :
          Component(mfr, mdl, p, "CPU"), clockSpeed(clock), coreCount(cores), socket(s) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Cores: " + std::to_string(coreCount) + ", Clock: " + std::to_string(clockSpeed) + "GHz, Socket: " + socket;
      }
  };

  class GPU : public Component {
  private:
      double clockSpeed;
      int VRAM;
      int VRAMSpeed;
  public:
      GPU(std::string mfr, std::string mdl, double p, double clock, int v, int vs) :
          Component(mfr, mdl, p, "GPU"), clockSpeed(clock), VRAM(v), VRAMSpeed(vs) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Clock: " + std::to_string(clockSpeed) + "MHz, VRAM: " + std::to_string(VRAM) + "GB, VRAM Speed: " + std::to_string(VRAMSpeed) + "MHz";
      }
  };

  class RAM : public Component {
  private:
      int size;
      int speed;
      std::string type;
  public:
      RAM(std::string mfr, std::string mdl, double p, int s, int spd, std::string t) :
          Component(mfr, mdl, p, "RAM"), size(s), speed(spd), type(t) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Size: " + std::to_string(size) + "GB, Speed: " + std::to_string(speed) + "MHz, Type: " + type;
      }
  };

  class Motherboard : public Component {
  private:
      int RAMSlots;
      std::string socket;
      int m2Slots;
  public:
      Motherboard(std::string mfr, std::string mdl, double p, int rs, std::string s, int m2) :
          Component(mfr, mdl, p, "Motherboard"), RAMSlots(rs), socket(s), m2Slots(m2) {}
      std::string getDetails() override {
          return Component::getDetails() + " - RAM Slots: " + std::to_string(RAMSlots) + ", Socket: " + socket + ", M.2 Slots: " + std::to_string(m2Slots);
      }
  };

  class CoolingSystem : public Component {
  private:
      int fanAmount;
      int temperature;
      std::string type;
  public:
      CoolingSystem(std::string mfr, std::string mdl, double p, int fa, int temp, std::string t) :
          Component(mfr, mdl, p, "Cooling"), fanAmount(fa), temperature(temp), type(t) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Fans: " + std::to_string(fanAmount) + ", Temp: " + std::to_string(temperature) + "°C, Type: " + type;
      }
  };

  class PSU : public Component {
  private:
      int wattage;
      std::string certification;
      std::string type;
  public:
      PSU(std::string mfr, std::string mdl, double p, int w, std::string cert, std::string t) :
          Component(mfr, mdl, p, "PSU"), wattage(w), certification(cert), type(t) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Wattage: " + std::to_string(wattage) + "W, Cert: " + certification + ", Type: " + type;
      }
  };

  class Storage : public Component {
  private:
      int capacity;
      int speed;
      std::string type;
  public:
      Storage(std::string mfr, std::string mdl, double p, int c, int s, std::string t) :
          Component(mfr, mdl, p, "Storage"), capacity(c), speed(s), type(t) {}
      std::string getDetails() override {
          return Component::getDetails() + " - Capacity: " + std::to_string(capacity) + "GB, Speed: " + std::to_string(speed) + "MB/s, Type: " + type;
      }
  };

  // Base Computer class
  class Computer {
  protected:
      std::vector<Component*> components;
      std::string name;
      std::string model;
  public:
      Computer(std::string n, std::string m) : name(n), model(m) {}
      virtual ~Computer() {
          for(auto comp : components) {
              delete comp;
          }
      }
      virtual std::string getSpecs() {
          std::string specs = "Name: " + name + "\nModel: " + model + "\nComponents:\n";
          for(auto comp : components) {
              specs += comp->getDetails() + "\n";
          }
          return specs;
      }
      void addComponent(Component* comp) {
          components.push_back(comp);
      }
      void removeComponent(int index) {
          if (index >= 0 && index < components.size()) {
              delete components[index];
              components.erase(components.begin() + index);
          }
      }
      void displaySpecs() {
          std::cout << getSpecs();
      }
  };

  class PC : public Computer {
  private:
      std::string caseType;
  public:
      PC(std::string n, std::string m, std::string ct) : Computer(n, m), caseType(ct) {}
      std::string getSpecs() override {
          return "PC Specifications:\n" + Computer::getSpecs() + "Case Type: " + caseType + "\n";
      }
  };

  class Laptop : public Computer {
  private:
      int batteryLife;
  public:
      Laptop(std::string n, std::string m, int bl) : Computer(n, m), batteryLife(bl) {}
      std::string getSpecs() override {
          return "Laptop Specifications:\n" + Computer::getSpecs() + "Battery Life: " + std::to_string(batteryLife) + " hours\n";
      }
  };

  class Server : public Computer {
  private:
      int rackSize;
  public:
      Server(std::string n, std::string m, int rs) : Computer(n, m), rackSize(rs) {}
      std::string getSpecs() override {
          return "Server Specifications:\n" + Computer::getSpecs() + "Rack Size: " + std::to_string(rackSize) + "U\n";
      }
  };

  int main() {
      PC desktop("Gaming PC", "Custom Build", "ATX Mid Tower");
      desktop.addComponent(new CPU("Intel", "i9-12900K", 589.99, 16, 5.2, "LGA1700"));
      desktop.addComponent(new GPU("NVIDIA", "RTX 3080", 699.99, 1800, 10, 19000));
      desktop.addComponent(new RAM("Corsair", "Vengeance", 199.99, 32, 3600, "DDR4"));
      desktop.addComponent(new Motherboard("ASUS", "ROG STRIX", 299.99, 4, "LGA1700", 2));
      desktop.addComponent(new CoolingSystem("NZXT", "Kraken", 159.99, 3, 65, "Liquid"));
      desktop.addComponent(new PSU("Corsair", "RM850x", 149.99, 850, "80+ Gold", "Modular"));
      desktop.addComponent(new Storage("Samsung", "970 EVO", 199.99, 1000, 3500, "NVMe SSD"));
      desktop.displaySpecs();

      Laptop notebook("Business Laptop", "ProBook", 8);
      notebook.addComponent(new CPU("AMD", "Ryzen 7 5800U", 449.99, 8, 4.4, "AM4"));
      notebook.addComponent(new RAM("Crucial", "DDR4", 89.99, 16, 3200, "DDR4"));
      notebook.addComponent(new GPU("AMD", "Radeon Integrated", 0, 2000, 8, 14000));
      notebook.addComponent(new Storage("Western Digital", "SN750", 129.99, 512, 3400, "NVMe SSD"));
      notebook.addComponent(new Motherboard("HP", "Custom", 299.99, 2, "AM4", 1));
      notebook.addComponent(new CoolingSystem("HP", "Standard", 49.99, 2, 75, "Air"));
      notebook.addComponent(new PSU("HP", "Standard", 79.99, 180, "80+ Bronze", "Integrated"));
      notebook.displaySpecs();

      Server rack("Web Server", "RackMount Pro", 4);
      rack.addComponent(new CPU("Intel", "Xeon E5-2699", 1499.99, 32, 3.6, "LGA2066"));
      rack.addComponent(new Storage("Samsung", "PM883", 399.99, 1920, 560, "SSD"));
      rack.addComponent(new RAM("Kingston", "Server RAM", 399.99, 128, 3200, "ECC DDR4"));
      rack.addComponent(new GPU("NVIDIA", "Tesla T4", 2499.99, 1590, 16, 16000));
      rack.addComponent(new Motherboard("Supermicro", "X11DPi-NT", 599.99, 16, "LGA2066", 4));
      rack.addComponent(new CoolingSystem("Noctua", "Industrial", 299.99, 6, 60, "Air"));
      rack.addComponent(new PSU("EVGA", "SuperNOVA", 299.99, 1600, "80+ Titanium", "Redundant"));
      rack.displaySpecs();

      return 0;
  }
