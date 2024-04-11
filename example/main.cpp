#include <iostream>
#include <fstream>

#include "classes/PHP.hpp"

PHP apiSettings(std::string located_at, bool usingTor = false) {
    PHP tmpPhp = PHP("", {""});//For tmp decrypt function
    std::string url, ct, prot, type, name, pw, j1, j2, j3, j4, j5, dq, sq;
    std::ifstream config(located_at);

    if (!config.is_open()) {
        throw std::runtime_error(located_at + " php api file not found.");
    }

    std::string tmpLine;
    int counter = 0;
    while (std::getline(config, tmpLine)) {
        ++counter;
        switch (counter) {
            case 1:
                url = tmpPhp.decrypt(tmpLine);
            break;
            case 2:
                ct = tmpPhp.decrypt(tmpLine);
            break;
            case 3:
                prot = tmpPhp.decrypt(tmpLine);
            break;
            case 4:
                type = tmpPhp.decrypt(tmpLine);
            break;
            case 5:
                name = tmpPhp.decrypt(tmpLine);
            break;
            case 6:
                pw = tmpPhp.decrypt(tmpLine);
            break;
            case 7:
                j1 = tmpPhp.decrypt(tmpLine);
            break;
            case 8:
                j2 = tmpPhp.decrypt(tmpLine);
            break;
            case 9:
                j3 = tmpPhp.decrypt(tmpLine);
            break;
            case 10:
                j4 = tmpPhp.decrypt(tmpLine);
            break;
            case 11:
                j5 = tmpPhp.decrypt(tmpLine);
            break;
            case 12:
                dq = tmpPhp.decrypt(tmpLine);
            break;
            case 13:
                sq = tmpPhp.decrypt(tmpLine);
            break;
        }
    }

    config.close();

    return PHP(url, {
        ct,//Content-Type
        prot,//Protocol
        type,//Type
        name,//Name
        pw,//Password
        j1,//Jellyfish 1
        j2,//Jellyfish 2
        j3,//Jellyfish 3
        j4,//Jellyfish 4
        j5,//Jellyfish 5
        dq,//Double quote code
        sq//Single quote code
    }, usingTor);
}

int main() {
    /**
    * --Steps to setup your PHP API--
    *
    * 1. Create the raw variable strings in the endpoint.php file that is on your VPS and your website. In this step, you can also add your database in endpoint.php
    *
    * 2. The goal is to get the raw data in the data.ini file (In the same order as in the endpoint.php file, per line. But your endpoint url at the first line.), but then encrypted. For that, you have to change the key string in the PHP.hpp class in cpp. Create a original key with the enc() function. It gives a bit more protection.
    * (dq and sq strings are for the replacement of double quotes and single ones. So the curl request string does not break.)
    * 3. Now you have a self-made key, you can continue by encrypting your raw config strings with your key in cpp. So create a empty PHP object, just as in the apiSettings function, and encrypt your raw strings to encrypted strings. just std::cout them and copy them. Place those in the data.ini file. (In the same order as the endpoint.php file! The first line is the url to your endpoint.php file, and only one line per variable.)
    *
    * 4. You are done! You can configure the endpoint.php for extra protection, by adding a mysqli db and logging wrong login attempts.
    * (Max data.ini filesize is 7kb | And use HTTPS endpoint link!)
    *
    *
    * --NEW--
    * Darkweb endpoint support!
    *
    * You can now link your .onion endpoint url if you want to.
    *
    * 1. Set the second parameter of the apiSettings function to true, to enable Tor service (darkweb engine)
    *
    * 2. Use a valid .onion address. And don't forget to exclude http:// and https://. So for example: ******.onion instead of https://******.onion.
    *
    * 3. Con: The API speed will decrease if you choose to use this option. Tor also keeps running in the background, but will not run again once it is active.
    *
    * 4. Pro: Your connection is more secure than before.
    *
    * 5. You can delete tor.exe and tor.vbs if you don't need the Tor service.
    *
    */
    PHP php = apiSettings("data/data.ini", true);//Using Tor
    std::string onlineCheck = php.execute({
        "die('online');"
    });
    if (onlineCheck == "error_no_access_endpoint") {
        std::cout << "Error. No access to PHP API. Press enter to exit.\n";
        system("set /p end=");
        return -1;
    }
    else if (onlineCheck != "online") {
        std::cout << "Error. No internet connection or the servers are down. Press enter to exit.\n";
        system("set /p end=");
        return -1;
    }
    std::string clientIp = php.execute({//Get the client IP addres using PHP
        "$ip = $_SERVER[\"REMOTE_ADDR\"];",
        "die($ip);"
    });

    std::cout << "Your ip addres: '" << clientIp << "'.\n";

    php.execute({
        "die(md5(\"" + clientIp + "\"));"
    });

    std::cout << "Your ip addres in md5 hash: '" << php.getLastResult() << "'.\n";

    std::cout << "Today is " << php.execute({
        "$today = date('Y-m-d h:i:s');",
        "die($today);"
    }) << ".\n";

    std::string name = "test";
    std::string pw = "1234";

    php.execute({//Interact with database in PHP
        "$name = htmlspecialchars(\"" + name + "\");",
        "$pw = htmlspecialchars(\"" + pw + "\");",
        "$push = $conn->prepare(\"INSERT INTO user(name, pw) VALUES(?, ?)\");",
        "$push->bind_param(\"ss\", $name, $pw);",
        "$push->execute();",
    });

    std::cout << "Thanks for using my API!\n\n(Made by wwwqr-000)\n";
    system("set /p end=");
    return 0;
}
