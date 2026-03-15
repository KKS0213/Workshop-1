#pragma once


void manager() {
    system("cls");
    string function[4] = { "Modify", "Masseur report", "Earning" ,"logout" };
    int choice = 99, n = sizeof(function) / sizeof(string);
    while (choice != 4) {
        system("cls");
        for (int i = 0; i < n; i++)
            cout << endl << left << i + 1 << "." << setw(5) << function[i];
        cout << "\n\nchoices: "; cin >> choice; cout << endl;
        if (choice == 1)
            modify();
        else if (choice == 2)
            report();
        else if (choice == 3)
            earning();
        else if (choice == 4) {
            system("cls");
            return;
        }
    }
}


void earning() {
    system("cls");
    string date[13] = { "NNN", "-01-%", "-02-%", "-03-%",  "-04-%", "-05-%", "-06-%", "-07-%", "-08-%",  "-09-%", "-10-%", "-11-%", "-12-%"};
    string month[12] = { "JANUARY", "FEBUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
    string year, truedate;
    int choice;
    double earn = 0;
    
    cout << "Earning for year: ";
    cin >> year;

    do{
        for (int i = 0; i < 12; i++)
            cout << endl << right << setw(5) << i + 1 << ". " << month[i];
        cout << "\n\nMonth: ";
        cin >> choice;
        if (choice > 12 || choice < 1)
            cout << "\nInvalid\n";
    } while (choice > 12 || choice < 1);

    truedate = year + date[choice];
    system("cls");

    cout << left << setw(15) << "\nPACKAGE" << setw(18) << "NAME" << setw(18) << "QUANTITY" << setw(10) << "PRICE"  << setw(10) << "EARNING" << endl;
    pstmt = con->prepareStatement(" SELECT package_id, package_name, COUNT(package_id), price, COUNT(package_id)*price FROM service NATURAL JOIN package WHERE appointment_date LIKE ? AND appointment_status = 'DONE' GROUP BY package_id");
    pstmt->setString(1, truedate);
    rs = pstmt->executeQuery();
    while (rs->next()) {
        cout << setprecision(2) << fixed << "   " << left << setw(7) << rs->getString(1) << setw(25) << rs->getString(2) << setw(15) << rs->getString(3) << setw(11) << rs->getDouble(4) << rs->getDouble(5) << endl;
        earn += rs->getDouble(5);
    }
    cout << setprecision(2) << fixed << "\nTotal earning: " << earn << endl;
    cout << "\n\nEnter 0 to quit: "; cin >> choice;
}


void report() {
    system("cls");
    string date[13] = { "NNN", "-01-%", "-02-%", "-03-%",  "-04-%", "-05-%", "-06-%", "-07-%", "-08-%",  "-09-%", "-10-%", "-11-%", "-12-%" };
    string month[12] = { "JANUARY", "FEBUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
    string feedback[5] = { "Worse", "Bad", "Neutral", "Good", "Excellent" };
    string year, truedate, mname[99], storemid[99], mid;
    int n = 0, choice;
    double quanfeed[5] = { 0,0,0,0,0 }, summin = 0, sumquan = 0, mark;

    cout << "Report for year: ";
    cin >> year;

    do {
        for (int i = 0; i < 12; i++)
            cout << endl << right << setw(5) << i + 1 << ". " << month[i];
        cout << "\n\nMonth: ";
        cin >> choice;
        if (choice > 12 || choice < 1)
            cout << "\nInvalid\n";
    } while (choice > 12 || choice < 1);

    truedate = year + date[choice];
    choice = 0;
    
    rs = stmt->executeQuery("SELECT masseur_id, mass_name FROM MASSEUR ORDER BY masseur_id");
    while (rs->next()) {
        storemid[n] = rs->getString(1);
        mname[n] = rs->getString(2);
        n++;
    }
    cout << "\nWhich masseur?\n";
    for (int i = 0; i < n; i++)
        cout << left << i + 1 << "." << setw(5) << mname[i] << endl;
    cout << "\nMasseur: "; cin >> choice;
    
    mid = storemid[choice - 1];
    system("cls");

    pstmt = con->prepareStatement("SELECT feedback, COUNT(feedback) FROM `service` WHERE masseur_id = ? AND appointment_status = 'DONE' AND appointment_date LIKE ? GROUP BY feedback");
    pstmt->setString(1, mid);
    pstmt->setString(2, truedate);
    rs = pstmt->executeQuery();
    while (rs->next()) {
        for(int i =0; i < 5; i++){
            if (i + 1 == rs->getInt(1))
                quanfeed[i] = rs->getDouble(2);
        }
    }
    cout << "\n" << "Masseur: " << mname[choice-1] << endl;
    cout << "\n    " << left << setw(20) << "FEEDBACK" << "QUANTITY\n\n";
    for (int i = 0; i < 5; i++)
        cout << setprecision(0) << fixed << "    " << left << setw(23) << feedback[i] << quanfeed[i] << endl;

    for (int i = 0; i < 5; i++) {
        summin  += (quanfeed[i] * (i + 1));
        sumquan += quanfeed[i];
    }

    mark = summin / sumquan;
    cout << setprecision(2) << fixed << "\nMark = " << mark;
    cout << "\n\nEnter 0 to quit: "; cin >> choice;
}


void modify() {
    string table[3] = { "masseur", "package", "time" };
    string func[4] = { "Update", "Delete", "Add", "Quit" };
    string mpart[4] = { "phone_num", "address", "skill", "status" };
    string ppart[2] = { "price", "duration" };
    string time[99];
    string table1, part, data[99], id, mname[99], name0, name1, search, address, add[99];
    int n = 99, choice, fun = 0, m = 0, ch0, a, mid[99]{}, mid0;

    while (fun != 4) {
        fun = 0, n = 99, m = 0, a = 0;
        system("cls");
        cout << "Which kind of modify would like to do\n\n";
        for (int i = 0; i < 4; i++)
            cout << i + 1 << ". " << func[i] << endl;
        cout << "\nChoice: ";
        cin >> fun;

        if (fun == 4)
            return;

        cout << "\nEnter 0 to quit any progression\n\nPick which field would like to modify\n\n";
        for (int i = 0; i < 3; i++)
            cout << i + 1 << ". " << table[i] << endl;
        cout << "\nField: ";
        cin >> choice;

        if (choice == 0) 
            goto finish;

        table1 = table[choice - 1];

        system("cls");

        // PACKAGE
        if (table1 == "package") {
            cout << left << setw(15) << "\nPACKAGE" << setw(16) << "NAME" << setw(11) << "PRICE" << setw(10) << "DURATION\n";
            rs = stmt->executeQuery("SELECT * FROM Package");
            while (rs->next()) {
                cout << endl << "   " << left << setw(8) << rs->getString(1) << setw(20) << rs->getString(2) << setw(10) << rs->getString(3) << setw(5) << rs->getString(4) << endl;
            }
            // Update
            if (fun == 1) {
                cout << endl;
                for (int i = 0; i < 2; i++)
                    cout << i + 1 << ". " << ppart[i] << endl;
                cout << "Update for part: ";
                cin >> n;
                if (n == 0)
                    goto finish;
                cout << "\nTo: ";
                getline(cin >> ws, part);
                if (part == "0")
                    goto finish;
                cout << "\nFor package: ";
                cin >> id;
                if (id == "0")
                    goto finish;
                settoupper(id);
                if (n == 1) {
                    pstmt = con->prepareStatement("UPDATE `package` SET price = ? WHERE `package_id` = ? ");
                    pstmt->setString(1, part);
                    pstmt->setString(2, id);
                    pstmt->execute();
                }
                else if (n == 2) {
                    pstmt = con->prepareStatement("UPDATE `package` SET duration = ? WHERE `package_id` = ? ");
                    pstmt->setString(1, part);
                    pstmt->setString(2, id);
                    pstmt->execute();
                }
            }
            // Delete
            else if (fun == 2) {
                cout << "\nWhich one would like to delete (package) : ";
                cin >> part;
                if (part == "0")
                    goto finish;
                settoupper(part);
                pstmt = con->prepareStatement("DELETE FROM `package` WHERE `package_id` =?");
                pstmt->setString(1, part);
                pstmt->execute();
            }
            // Add
            else if (fun == 3) {
                cout << "\nAdd data";
                cout << "\nPackage: "; cin >> data[0];
                if (data[0] == "0")
                    goto finish;
                settoupper(data[0]);
                cout << "\nName: "; getline(cin >> ws, data[1]);
                if (data[1] == "0")
                    goto finish;
                cout << "\nPrice: "; cin >> data[2];
                if (data[2] == "0")
                    goto finish;
                cout << "\nDuration: "; getline(cin >> ws, data[3]);
                if (data[3] == "0")
                    goto finish;

                pstmt = con->prepareStatement("INSERT INTO `package`(`package_id`, `package_name`, `price`, `duration`) VALUES (?,?,?,?)");
                pstmt->setString(1, data[0]);
                pstmt->setString(2, data[1]);
                pstmt->setString(3, data[2]);
                pstmt->setString(4, data[3]);
                pstmt->execute();
            }
        }

        // MASSEUR 
        else if (table1 == "masseur") {
            if (fun != 3) {
            cout << "Name for searching: "; getline(cin >> ws, name0);
            settoupper(name0);
            search = "%" + name0 + "%";
            system("cls");
            cout << left << setw(9) << "\nNO" << setw(20) << "MASSEUR" << setw(10) << "GENDER" << setw(20) << "PHONE NUMBER" << setw(20) << "SKILL" << "STATUS\n";
            pstmt = con->prepareStatement("SELECT * FROM `masseur` WHERE `mass_name` LIKE ?");
            pstmt->setString(1, search);
            rs = pstmt->executeQuery();
            while (rs->next()) {
                cout << endl << " " << left << setw(7) << a + 1 << setw(20) << rs->getString(2) << setw(10) << rs->getString(3) << setw(20) << rs->getString(4) << setw(20) << rs->getString(6) << rs->getString(7);
                mname[a] = rs->getString(2);
                add[a] = rs->getString(5);
                mid[a] = rs->getInt(1);
                a++;
            }
                cout << "\n\nSELECT: "; 
                cin >> ch0;
                if (ch0 == 0)
                    goto finish;

                name1 = mname[ch0 - 1];
                address = add[ch0 - 1];
                mid0 = mid[ch0 - 1];
            }
            // Update
            if (fun == 1) {
                cout << endl;
                for (int i = 0; i < 4; i++)
                    cout << i + 1 << ". " << mpart[i] << endl;
                cout << "Update for part: ";
                cin >> n;
                if (n == 2) {
                    cout << "\nOld address: " << address << endl;
                }
                else if (n == 0)
                    goto finish;
                cout << "\nTo: ";
                getline(cin >> ws, part);
                settoupper(part);
                if (part == "0")
                    goto finish;
                if (n == 1) {
                    pstmt = con->prepareStatement("UPDATE `masseur` SET `phone_num` = ? WHERE `mass_name` = ? ");
                    pstmt->setString(1, part);
                    pstmt->setString(2, name1);
                    pstmt->execute();
                }
                else if (n == 2) {
                    pstmt = con->prepareStatement("UPDATE `masseur` SET `address` = ? WHERE `mass_name` = ?");
                    pstmt->setString(1, part);
                    pstmt->setString(2, name1);
                    pstmt->execute();
                }
                else if (n == 3) {
                    pstmt = con->prepareStatement("UPDATE `masseur` SET `skill` = ? WHERE `mass_name` = ? ");
                    pstmt->setString(1, part);
                    pstmt->setString(2, name1);
                    pstmt->execute();
                }
                else if (n == 4) {
                    pstmt = con->prepareStatement("UPDATE `masseur` SET `status` = ? WHERE `mass_name` = ? ");
                    pstmt->setString(1, part);
                    pstmt->setString(2, name1);
                    pstmt->execute();
                }
            }
            // Delete
            else if (fun == 2) {
                pstmt = con->prepareStatement("DELETE FROM `service` WHERE `masseur_id` = ?");
                pstmt->setInt(1, mid0);
                pstmt->execute();

                pstmt = con->prepareStatement("DELETE FROM `masseur` WHERE `mass_name` = ?");
                pstmt->setString(1, name1);
                pstmt->execute();
            }
            // Add
            else if (fun == 3) {
                cout << "\nAdd data";
                cout << "\nName: "; getline(cin >> ws, data[0]);
                if (data[0] == "0")
                    goto finish;
                settoupper(data[0]);
                cout << "\nGender: "; getline(cin >> ws, data[1]);
                if (data[1] == "0")
                    goto finish;
                settoupper(data[1]);
                cout << "\nPhone number: "; cin >> data[2];
                if (data[2] == "0")
                    goto finish;
                cout << "\nAddress: "; getline(cin >> ws, data[3]);
                if (data[3] == "0")
                    goto finish;
                settoupper(data[3]);
                cout << "\nSkill: "; getline(cin >> ws, data[4]);
                if (data[4] == "0")
                    goto finish;
                settoupper(data[4]);
                cout << "\nStatus(active/inative): "; getline(cin >> ws, data[5]);
                if (data[5] == "0")
                    goto finish;
                settoupper(data[5]);

                pstmt = con->prepareStatement("INSERT INTO `masseur`(`mass_name`, `gender`, `phone_num`, `address`, `skill`, `status`) VALUES (?,?,?,?,?,?)");
                pstmt->setString(1, data[0]);
                pstmt->setString(2, data[1]);
                pstmt->setString(3, data[2]);
                pstmt->setString(4, data[3]);
                pstmt->setString(5, data[4]);
                pstmt->setString(6, data[5]);
                pstmt->execute();
            }

        }
        //TIME
        else if (table1 == "time") {
            rs = stmt->executeQuery("SELECT reserve_time FROM time");
            while (rs->next()) {
                time[m] = rs->getString(1);
                m++;
            }

            cout << "\nReserve time\n";
            for (int i = 0; i < m; i++)
                cout << left << i + 1 << "." << setw(5) << time[i] << endl;
            // Update
            if (fun == 1) {
                cout << "SELECT: "; cin >> ch0;
                if (ch0 == 0)
                    goto finish;
                id = time[ch0 - 1];
                cout << "\nTo: ";
                getline(cin >> ws, part);
                if (part == "0")
                    goto finish;
                pstmt = con->prepareStatement("UPDATE `time` SET `reserve_time`= ? WHERE `reserve_time` = ?");
                pstmt->setString(1, part);
                pstmt->setString(2, id);
                pstmt->execute();
            }
            // Delete
            else if (fun == 2) {
                cout << "SELECT: "; cin >> ch0;
                if (ch0 == 0)
                    goto finish;
                id = time[ch0 - 1];
                pstmt = con->prepareStatement("DELETE FROM `time` WHERE `reserve_time` = ?");
                pstmt->setString(1, id);
                pstmt->execute();
            }
            // Add
            else if (fun == 3) {
                cout << "\nAdd data";
                cout << "\nTime : "; cin >> data[0];
                if (data[0] == "0")
                    goto finish;

                pstmt = con->prepareStatement("INSERT INTO `time`(`reserve_time`) VALUES (?)");
                pstmt->setString(1, data[0]);
                pstmt->execute();
            }


        }
    finish:
        ;
    }
}
