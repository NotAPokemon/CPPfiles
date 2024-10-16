#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <future>

//ifstream is read
//ofstream is write

std::string readF(std::string path) {
  std::ifstream file(path);
  std::string data;
  std::string Fdata;
  while (getline(file, data)) {
    Fdata += data;
  };
  return Fdata;
};

std::string d(){
  return "\nlineforuseonlybyprintstatement = 0\n\nwith open(\"o.json\",\"w\") as f:\n\tx = {}\n\tjson.dump(x,f)\n\ndef print(x):\n\tglobal lineforuseonlybyprintstatement\n\tlineforuseonlybyprintstatement+=1\n\tdata = {str(lineforuseonlybyprintstatement):x}\n\twith open(\"o.json\",\"r\") as f:\n\t\to = json.load(f)\n\t\to.update(data)\n\t\tdata = o\n\twith open(\"o.json\",\"w\") as f:\n\t\tjson.dump(data,f,indent=4)\n\ntry:\n";
}

std::string readF(std::ifstream file) {
  std::string data;
  std::string Fdata;
  while (getline(file, data)) {
    Fdata += data;
  };
  return Fdata;
};

class file {
  private:
    std::string Spath;
    std::string SOdata;
    std::string Name;
    std::string Imports = "import json\n";
    std::string end = "\nexcept Exception as e:\n\tlineforuseonlybyprintstatement = 0\n\tprint(e)\n";
    std::string Default = d();
    bool Py;

  public:
    file(std::string path, std::string name) {
      Spath = path;
      SOdata = "";
      Name = name;
    }

    std::string getPath() {
      return Spath;
    }

    int write(std::string data) {
      try {
        std::ofstream SWfile(Spath);
        SWfile << Imports << Default << "\n\t" << SOdata << "\n\t" << data << "\n\t" << end;
        data = data + "\n\t";
        SOdata += data;
        SWfile.close();
        return 0;
      } catch (...) {
        return 1;
      };
    }

    int overWrite(std::string data) {
      try {
        std::ofstream SWfile(Spath);
        SWfile << Imports << Default << "\n\t" << data << end;
        SWfile.close();
        return 0;
      } catch (...) {
        return 1;
      };
    }

    std::string read() {
      return readF(Spath);
    }

    void PyIfy(){
      if (Py == false) {
        Py = true;
      } else {
        Py = false;
      }
    }

    void del(){
      char path[] = "main.py";
      remove(path);
      char path2[] = "o.json";
      remove(path2);
    }
      
    int runFile(){
      if (Py == true){
        std::string command = "python -m" + Name;
        int result = system(command.c_str());
        if (result != 0) {
          std::cout << result;
        }
        return result;
      } else {
        return 1;
      }
    }

    int addImport(std::string import) {
      Imports += import + "\n";
      return 0;
    }

    std::string getResult(int x) {
      if (x == 0) {
        bool get = false;
        std::string res = readF("o.json");
        std::string Fres = "";
        for (int i = 0; i < res.length(); i++) {
          if(res[i] == ',') {
            get = false;
            Fres += "\n";
          }
          if(res[i] == '}') {
            get = false;
            Fres += "\n";
          }
          if (res[i] == ':') {
            get = true;
            continue;
          } 
          if (get == true) {
            Fres += res[i];
          }
          
        }
        for (int i = 0; i < Fres.length(); i++) {
          if (i == 0) {
            Fres[i] = '\b';
          }
          if (Fres[i] == '"') {
            Fres[i] = '\b';
          }
        }
        return Fres;
      } else {
        return "\nfailed";
      }
    }


};


int main() {
  file x = file("main.py","main");
  x.addImport("from flask import Flask");
  x.addImport("from waitress import serve");
  x.write("app = Flask(__name__)");
  x.write("\n");
  x.write("@app.route('/')");
  x.write("def hello_world():");
  x.write("\treturn 'Hello, JJ!'");
  x.write("\n");
  x.write("if __name__ == '__main__':");
  x.write("\tserve(app, host='0.0.0.0', port=5000)");
  x.PyIfy();
  std::cout << x.getResult(x.runFile());
  x.del();
  
  return 0;
}