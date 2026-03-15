#pragma once


void login() {
    string position[99], pos, pwd;
    int n = 0, i = 0, choice = 99;
    bool c = 1;

    rs = stmt->executeQuery("SELECT pos FROM ACCOUNT");
    while (rs->next()) {
        position[n] = rs->getString(1);
        n++;
    }
    position[n] = "quit";
    while (c) {
        while (choice > n || choice <=0) {
            cout << "Welcome to masseur tracking system. Please identify user level.\n" << endl;
            for (int i = 0; i <= n; i++)
                cout << left << i + 1 << "." << setw(5) << position[i] << endl;
            cout << "\nuser: ";  cin >> choice;
            if (position[choice - 1] == "quit") {
                return;
            }
            else if (choice > n + 1 || choice <= 0) {
                system("cls");
                cout << "invalid choice\n\n";
            }
        }
        pos = position[choice - 1];
        cout << "password: "; cin >> pwd;
        pstmt = con->prepareStatement("SELECT pwd from ACCOUNT where pos = ?");
        pstmt->setString(1, pos);
        rs = pstmt->executeQuery();
        while (rs->next()) {
            if (pwd != rs->getString(1)) {
                system("cls");
                cout << "wrong password\n" << endl;
            }
            else if (position[choice - 1] == "MANAGER")
                manager();
            else if (position[choice - 1] == "STAFF")
                staff();

        }
        choice = 99;
    }

}

void settoupper(string& p) {
    transform(p.begin(), p.end(), p.begin(), ::toupper);
}