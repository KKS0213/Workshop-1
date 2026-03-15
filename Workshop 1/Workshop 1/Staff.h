#pragma once


void staff() {
    string function[3] = { "add appointment", "update appointment", "logout" };
    int choice = 99, n = sizeof(function) / sizeof(string);

    while (choice != 3) {
        system("cls");
        cout << left << setw(15) << "\nSERVICE ID" << setw(28) << "CUSTOMER" << setw(18) << "PHONE NUMBER" << setw(15) << "PACKAGE" << setw(21) << "MASSEUR" << setw(15) << "DATE" << setw(10) << "TIME\n";
        rs = stmt->executeQuery("SELECT service_id, cust_name, customer.phone_num, package_id, mass_name, appointment_date, appointment_time FROM `service` JOIN customer USING(cust_id) JOIN masseur USING(masseur_id) WHERE appointment_status = 'RESERVED' ORDER BY service_id");
        while (rs->next()) {
            cout << endl << "   " << left << setw(10) << rs->getString(1) << setw(30) << rs->getString(2) << setw(20) << rs->getString(3) << setw(10) << rs->getString(4) << setw(20) << rs->getString(5) << setw(18) << rs->getString(6) << rs->getString(7);
        }
        
        cout << "\n\nEnter 0 to quit cancel any progress to add or update appointment";
        cout << "\n\nWhat would you like to do?\n";
        for (int i = 0; i < n; i++)
            cout << endl << left << i + 1 << "." << setw(5) << function[i];
        
        cout << "\n\nchoices: "; cin >> choice; cout << endl;
        if (choice == 1)
            addappointment();
        else if (choice == 2)
            updateappointment();
        else if (choice == 3) {
            system("cls");
            return;
        }
    }
}


void addappointment() {
    system("cls");
    string ph, cus, cid, gen, mid, time, date, package, service;
    int n = 0, choice;
    string mname[99], midd[99], timee[99];
    bool check = false;

        cout << "Name: "; getline(cin >> ws, cus);
        if (cus == "0") {
            system("cls");
            return;
        }
        settoupper(cus);
        cout << "Phone Number: "; cin >> ph;
        if (ph == "0"){ 
            system("cls");
            return; 
        }
        pstmt = con->prepareStatement("SELECT cust_id FROM customer WHERE cust_name = ? AND phone_num = ? HAVING cust_id IS NOT NULL");
        pstmt->setString(1, cus);
        pstmt->setString(2, ph);
        rs = pstmt->executeQuery();
        if (rs->next() == false) {
            cout << "Gender(male/female): "; cin >> gen;
            if (gen == "0") {
                system("cls");
                return;
            }
            settoupper(gen);
            pstmt = con->prepareStatement("INSERT INTO `customer`(cust_name, gender, phone_num) VALUES (?,?,?);");
            pstmt->setString(1, cus);
            pstmt->setString(2, gen);
            pstmt->setString(3, ph);
            pstmt->execute();
            system("cls");
            cout << "\nNew customer added\n";
        }

        pstmt = con->prepareStatement("SELECT cust_id FROM customer WHERE cust_name = ? AND phone_num = ? HAVING cust_id IS NOT NULL");
        pstmt->setString(1, cus);
        pstmt->setString(2, ph);
        rs = pstmt->executeQuery();
        while (rs->next()) {
            cid = rs->getString(1);
        }

        cout << left << setw(15) << "\nPACKAGE" << setw(16) << "NAME" << setw(11) << "PRICE" << setw(10) << "DURATION\n";
        rs = stmt->executeQuery("SELECT * FROM Package");
        while (rs->next()) {
            cout << endl << "   " << left << setw(8) << rs->getString(1) << setw(20) << rs->getString(2) << setw(10) << rs->getString(3) << setw(5) << rs->getString(4) << endl;
        }
        cout << "\nPackage: "; cin >> package;
        if (package == "0") {
            system("cls");
            return;
        }
        system("cls");
        settoupper(package);
        if (package == "A" || package == "B" || package == "C" || package == "D")
            service = "massage";
        else if (package == "E")
            service = "ear scrapping";
        pstmt = con->prepareStatement("SELECT masseur_id, mass_name FROM MASSEUR WHERE skill = ? and status = 'ACTIVE' ORDER BY masseur_id");
        pstmt->setString(1, service);
        rs = pstmt->executeQuery();
        while (rs->next()) {
            midd[n] = rs->getString(1);
            mname[n] = rs->getString(2);
            n++;
        }
        for (int i = 0; i < n; i++)
            cout << left << i + 1 << "." << setw(5) << mname[i] << endl;
        cout << "\nMasseur: "; cin >> choice;
        if (choice == 0) {
            system("cls");
            return;
        }
        system("cls");
        mid = midd[choice - 1];
        cout << "\nDate(yyyy-mm-dd): "; cin >> date;
        if (date == "0") {
            system("cls");
            return;
        }
        n = 0, choice = 0;
 
        pstmt = con->prepareStatement("SELECT reserve_time FROM time EXCEPT SELECT appointment_time FROM `service` WHERE masseur_id = ? AND appointment_date = ?");
        pstmt->setString(1, mid);
        pstmt->setString(2, date);
        rs = pstmt->executeQuery();
        while (rs->next()) {
            timee[n] = rs->getString(1);
            n++;
        }
        cout << "\nReserve time\n";
        for (int i = 0; i < n; i++)
            cout << left << i + 1 << "." << setw(5) << timee[i] << endl;
        cout << "SELECT: "; cin >> choice;
        if (choice == 0) {
            system("cls");
            return;
        }
        time = timee[choice - 1];
        system("cls");
        pstmt = con->prepareStatement("INSERT INTO service( cust_id, package_id, masseur_id, appointment_date, appointment_time, appointment_status) VALUES (?,?,?,?,?,'RESERVED')");
        pstmt->setString(1, cid);
        pstmt->setString(2, package);
        pstmt->setString(3, mid);
        pstmt->setString(4, date);
        pstmt->setString(5, time);
        pstmt->execute();
        cout << "\nAppointment added\n";
}


void updateappointment() {
    system("cls");
    int id, choice;
    string fdbck[5] = {"Worse", "Bad", "Neutral", "Good", "Excellent"};
    int n = sizeof(fdbck) / sizeof(string);
    bool c = true;
    
    cout << left << setw(15) << "\nSERVICE ID" << setw(28) << "CUSTOMER" << setw(18) << "PHONE NUMBER" << setw(15) << "PACKAGE" << setw(21) << "MASSEUR" << setw(15) << "DATE" << setw(10) << "TIME\n";
    rs = stmt->executeQuery("SELECT service_id, cust_name, customer.phone_num, package_id, mass_name, appointment_date, appointment_time FROM `service` JOIN customer USING(cust_id) JOIN masseur USING(masseur_id) WHERE appointment_status = 'RESERVED' ORDER BY service_id");
    while (rs->next()) {
        cout << endl << "   " << left << setw(10) << rs->getString(1) << setw(30) << rs->getString(2) << setw(20) << rs->getString(3) << setw(10) << rs->getString(4) << setw(20) << rs->getString(5) << setw(18) << rs->getString(6) << rs->getString(7);
    }

    do {
        c = true;
        cout << "\n\nService ID: ";
        cin >> id;
        if (id == 0) {
            system("cls");
            return;
        }
        pstmt = con->prepareStatement("SELECT service_id FROM service WHERE appointment_status = 'RESERVED' AND service_id = ? HAVING service_id IS NOT NULL;");
        pstmt->setInt(1, id);
        rs = pstmt->executeQuery();
        if (rs->next() == false) {
            cout << "\nInvalid. Do again.\n";
            c = false;
        }
    } while(c == false);
   
    do {
        for (int i = 0; i < n; i++)
            cout << endl << left << i + 1 << "." << setw(5) << fdbck[i];
        cout << "\n\nFeedback: "; cin >> choice; 
        if (choice == 0) {
            system("cls");
            return;
        }
        choice > 6 ? cout << "Invalid.Do again.\n": cout << endl;
    } while (choice > n);
    pstmt = con->prepareStatement("UPDATE service SET appointment_status ='DONE', feedback = ? WHERE service_id = ?");
    pstmt->setInt(1, choice);
    pstmt->setInt(2, id);
    pstmt->execute();
    system("cls");
    cout << "\nAppointment updated\n";
}
