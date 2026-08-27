#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// FILES
// ============================================================

const string PATIENT_FILE = "patients.txt";
const string DOCTOR_FILE = "doctors.txt";
const string APPOINTMENT_FILE = "appointments.txt";
const string BILL_FILE = "bills.txt";

// ============================================================
// CONSTANTS
// ============================================================

const double REGISTRATION_FEE = 200.0;
const double BED_CHARGE_PER_DAY = 1500.0;
const double CONSULTATION_FEE = 500.0;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string currentDate()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << local->tm_mday
       << "-"
       << setw(2) << local->tm_mon + 1
       << "-"
       << local->tm_year + 1900;

    return ss.str();
}

string currentTime()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << local->tm_hour
       << ":"
       << setw(2) << local->tm_min
       << ":"
       << setw(2) << local->tm_sec;

    return ss.str();
}

time_t dateToTime(const string& date)
{
    int day, month, year;
    char separator;

    stringstream ss(date);

    ss >> day >> separator >> month >> separator >> year;

    tm t = {};
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    t.tm_hour = 12;

    return mktime(&t);
}

int daysBetween(const string& start, const string& end)
{
    time_t startTime = dateToTime(start);
    time_t endTime = dateToTime(end);

    double difference =
        difftime(endTime, startTime);

    int days =
        static_cast<int>(
            difference / (60 * 60 * 24)
        );

    return max(1, days);
}

// ============================================================
// DOCTOR CLASS
// ============================================================

class Doctor
{
private:
    int id;
    string name;
    string specialization;
    bool available;

public:

    Doctor()
    {
        id = 0;
        available = true;
    }

    Doctor(
        int id,
        const string& name,
        const string& specialization,
        bool available = true)
        :
        id(id),
        name(name),
        specialization(specialization),
        available(available)
    {
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getSpecialization() const
    {
        return specialization;
    }

    bool isAvailable() const
    {
        return available;
    }

    void setAvailability(bool status)
    {
        available = status;
    }

    void display() const
    {
        cout << left
             << setw(8) << id
             << setw(25) << name
             << setw(25) << specialization
             << setw(15)
             << (available ? "Available" : "Busy")
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << id << "|"
           << name << "|"
           << specialization << "|"
           << available;

        return ss.str();
    }
};

// ============================================================
// PATIENT CLASS
// ============================================================

class Patient
{
private:

    int id;
    string name;
    int age;
    string gender;
    string phone;
    string disease;

    int doctorId;
    bool admitted;

    string admissionDate;
    string dischargeDate;

    // Emergency priority
    int priority;

public:

    Patient()
    {
        id = 0;
        age = 0;
        doctorId = -1;
        admitted = false;
        priority = 5;
    }

    Patient(
        int id,
        const string& name,
        int age,
        const string& gender,
        const string& phone,
        const string& disease,
        int priority)
        :
        id(id),
        name(name),
        age(age),
        gender(gender),
        phone(phone),
        disease(disease),
        doctorId(-1),
        admitted(false),
        admissionDate(""),
        dischargeDate(""),
        priority(priority)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getGender() const
    {
        return gender;
    }

    string getPhone() const
    {
        return phone;
    }

    string getDisease() const
    {
        return disease;
    }

    int getDoctorId() const
    {
        return doctorId;
    }

    bool isAdmitted() const
    {
        return admitted;
    }

    string getAdmissionDate() const
    {
        return admissionDate;
    }

    string getDischargeDate() const
    {
        return dischargeDate;
    }

    int getPriority() const
    {
        return priority;
    }

    // ========================================================
    // DOCTOR ASSIGNMENT
    // ========================================================

    void assignDoctor(int id)
    {
        doctorId = id;
    }

    // ========================================================
    // ADMIT
    // ========================================================

    void admit()
    {
        admitted = true;
        admissionDate = currentDate();
        dischargeDate = "";
    }

    // ========================================================
    // DISCHARGE
    // ========================================================

    void discharge()
    {
        admitted = false;
        dischargeDate = currentDate();
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << "\n============================================\n";
        cout << "              PATIENT RECORD\n";
        cout << "============================================\n";

        cout << "Patient ID       : " << id << '\n';
        cout << "Name             : " << name << '\n';
        cout << "Age              : " << age << '\n';
        cout << "Gender           : " << gender << '\n';
        cout << "Phone            : " << phone << '\n';
        cout << "Disease          : " << disease << '\n';

        cout << "Doctor ID        : ";

        if (doctorId == -1)
            cout << "Not Assigned\n";
        else
            cout << doctorId << '\n';

        cout << "Emergency Level  : "
             << priority << '\n';

        cout << "Status           : "
             << (admitted ? "Admitted" : "Not Admitted")
             << '\n';

        cout << "Admission Date   : "
             << (admissionDate.empty()
                 ? "N/A"
                 : admissionDate)
             << '\n';

        cout << "Discharge Date   : "
             << (dischargeDate.empty()
                 ? "N/A"
                 : dischargeDate)
             << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << id << "|"
           << name << "|"
           << age << "|"
           << gender << "|"
           << phone << "|"
           << disease << "|"
           << doctorId << "|"
           << admitted << "|"
           << admissionDate << "|"
           << dischargeDate << "|"
           << priority;

        return ss.str();
    }

    void restore(
        int doctor,
        bool admissionStatus,
        const string& admission,
        const string& discharge)
    {
        doctorId = doctor;
        admitted = admissionStatus;
        admissionDate = admission;
        dischargeDate = discharge;
    }
};

// ============================================================
// APPOINTMENT STRUCT
// ============================================================

struct Appointment
{
    int patientId;
    int doctorId;
    string date;
    string time;
    int priority;
};

// Priority queue comparator
struct AppointmentCompare
{
    bool operator()(
        const Appointment& a,
        const Appointment& b) const
    {
        // Lower priority number = higher priority

        if (a.priority != b.priority)
            return a.priority > b.priority;

        if (a.date != b.date)
            return a.date > b.date;

        return a.time > b.time;
    }
};

// ============================================================
// BILL CLASS
// ============================================================

class Bill
{
private:

    int patientId;
    double registrationFee;
    double consultationFee;
    double bedCharges;
    double total;

public:

    Bill(
        int patientId,
        double registrationFee,
        double consultationFee,
        double bedCharges)
        :
        patientId(patientId),
        registrationFee(registrationFee),
        consultationFee(consultationFee),
        bedCharges(bedCharges)
    {
        total =
            registrationFee +
            consultationFee +
            bedCharges;
    }

    double getTotal() const
    {
        return total;
    }

    void display() const
    {
        cout << "\n============================================\n";
        cout << "               PATIENT BILL\n";
        cout << "============================================\n";

        cout << "Patient ID          : "
             << patientId << '\n';

        cout << fixed << setprecision(2);

        cout << "Registration Fee    : Rs. "
             << registrationFee << '\n';

        cout << "Consultation Fee    : Rs. "
             << consultationFee << '\n';

        cout << "Bed Charges         : Rs. "
             << bedCharges << '\n';

        cout << "--------------------------------------------\n";

        cout << "TOTAL BILL          : Rs. "
             << total << '\n';

        cout << "============================================\n";
    }

    string serialize() const
    {
        stringstream ss;

        ss << patientId << "|"
           << registrationFee << "|"
           << consultationFee << "|"
           << bedCharges << "|"
           << total;

        return ss.str();
    }
};

// ============================================================
// HOSPITAL CLASS
// ============================================================

class Hospital
{
private:

    vector<Patient> patients;
    vector<Doctor> doctors;

    priority_queue<
        Appointment,
        vector<Appointment>,
        AppointmentCompare
    > appointmentQueue;

    int nextPatientId = 1001;

public:

    // ========================================================
    // LOAD PATIENTS
    // ========================================================

    void loadPatients()
    {
        ifstream file(PATIENT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string ageStr;
            string gender;
            string phone;
            string disease;
            string doctorStr;
            string admittedStr;
            string admissionDate;
            string dischargeDate;
            string priorityStr;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, ageStr, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');
            getline(ss, disease, '|');
            getline(ss, doctorStr, '|');
            getline(ss, admittedStr, '|');
            getline(ss, admissionDate, '|');
            getline(ss, dischargeDate, '|');
            getline(ss, priorityStr, '|');

            Patient patient(
                stoi(idStr),
                name,
                stoi(ageStr),
                gender,
                phone,
                disease,
                stoi(priorityStr)
            );

            patient.restore(
                stoi(doctorStr),
                stoi(admittedStr),
                admissionDate,
                dischargeDate
            );

            patients.push_back(patient);

            if (patient.getId() >= nextPatientId)
                nextPatientId = patient.getId() + 1;
        }

        file.close();
    }

    // ========================================================
    // SAVE PATIENTS
    // ========================================================

    void savePatients()
    {
        ofstream file(PATIENT_FILE);

        for (const auto& patient : patients)
        {
            file << patient.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD DOCTORS
    // ========================================================

    void loadDoctors()
    {
        ifstream file(DOCTOR_FILE);

        if (!file)
        {
            // Default doctors
            doctors.emplace_back(
                1,
                "Dr. Sharma",
                "General Medicine"
            );

            doctors.emplace_back(
                2,
                "Dr. Mehta",
                "Cardiology"
            );

            doctors.emplace_back(
                3,
                "Dr. Verma",
                "Neurology"
            );

            doctors.emplace_back(
                4,
                "Dr. Singh",
                "Orthopedics"
            );

            doctors.emplace_back(
                5,
                "Dr. Kapoor",
                "Pediatrics"
            );

            saveDoctors();

            return;
        }

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string specialization;
            string availabilityStr;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, specialization, '|');
            getline(ss, availabilityStr, '|');

            doctors.emplace_back(
                stoi(idStr),
                name,
                specialization,
                stoi(availabilityStr)
            );
        }

        file.close();
    }

    // ========================================================
    // SAVE DOCTORS
    // ========================================================

    void saveDoctors()
    {
        ofstream file(DOCTOR_FILE);

        for (const auto& doctor : doctors)
        {
            file << doctor.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // SAVE BILL
    // ========================================================

    void saveBill(const Bill& bill)
    {
        ofstream file(
            BILL_FILE,
            ios::app
        );

        file << bill.serialize() << '\n';

        file.close();
    }

    // ========================================================
    // FIND PATIENT
    // ========================================================

    Patient* findPatient(int patientId)
    {
        for (auto& patient : patients)
        {
            if (patient.getId() == patientId)
                return &patient;
        }

        return nullptr;
    }

    // ========================================================
    // FIND DOCTOR
    // ========================================================

    Doctor* findDoctor(int doctorId)
    {
        for (auto& doctor : doctors)
        {
            if (doctor.getId() == doctorId)
                return &doctor;
        }

        return nullptr;
    }

    // ========================================================
    // REGISTER PATIENT
    // ========================================================

    void registerPatient()
    {
        string name;
        int age;
        string gender;
        string phone;
        string disease;
        int priority;

        clearInput();

        cout << "\n============================================\n";
        cout << "             PATIENT REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Patient Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        clearInput();

        cout << "Enter Gender: ";
        getline(cin, gender);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Disease/Problem: ";
        getline(cin, disease);

        // Emergency priority
        cout << "\nEmergency Priority:\n";
        cout << "1 - Critical Emergency\n";
        cout << "2 - Serious\n";
        cout << "3 - Moderate\n";
        cout << "4 - Mild\n";
        cout << "5 - Normal\n";

        do
        {
            cout << "Enter Priority Level: ";
            cin >> priority;

            if (priority < 1 || priority > 5)
                cout << "Please enter a value between 1 and 5.\n";

        } while (priority < 1 || priority > 5);

        Patient patient(
            nextPatientId,
            name,
            age,
            gender,
            phone,
            disease,
            priority
        );

        patients.push_back(patient);

        savePatients();

        cout << "\nPatient registered successfully!\n";

        cout << "Patient ID: "
             << nextPatientId << '\n';

        nextPatientId++;
    }

    // ========================================================
    // DISPLAY DOCTORS
    // ========================================================

    void displayDoctors()
    {
        cout << "\n";
        cout << "========================================================\n";
        cout << "                    DOCTOR LIST\n";
        cout << "========================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(25) << "Name"
             << setw(25) << "Specialization"
             << setw(15) << "Status"
             << '\n';

        cout << string(73, '-') << '\n';

        for (const auto& doctor : doctors)
        {
            doctor.display();
        }

        cout << "========================================================\n";
    }

    // ========================================================
    // ASSIGN DOCTOR
    // ========================================================

    void assignDoctor()
    {
        int patientId;
        int doctorId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        displayDoctors();

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;

        Doctor* doctor = findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor not found.\n";
            return;
        }

        if (!doctor->isAvailable())
        {
            cout << "Doctor is currently busy.\n";
            return;
        }

        patient->assignDoctor(doctorId);

        doctor->setAvailability(false);

        savePatients();
        saveDoctors();

        cout << "\nDoctor assigned successfully!\n";

        cout << "Doctor: "
             << doctor->getName()
             << '\n';
    }

    // ========================================================
    // ADMIT PATIENT
    // ========================================================

    void admitPatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        if (patient->isAdmitted())
        {
            cout << "Patient is already admitted.\n";
            return;
        }

        patient->admit();

        savePatients();

        cout << "\nPatient admitted successfully!\n";

        cout << "Admission Date: "
             << patient->getAdmissionDate()
             << '\n';
    }

    // ========================================================
    // DISCHARGE PATIENT
    // ========================================================

    void dischargePatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        if (!patient->isAdmitted())
        {
            cout << "Patient is not currently admitted.\n";
            return;
        }

        patient->discharge();

        // Make assigned doctor available
        if (patient->getDoctorId() != -1)
        {
            Doctor* doctor =
                findDoctor(patient->getDoctorId());

            if (doctor != nullptr)
            {
                doctor->setAvailability(true);
            }
        }

        savePatients();
        saveDoctors();

        cout << "\nPatient discharged successfully!\n";

        cout << "Discharge Date: "
             << patient->getDischargeDate()
             << '\n';

        // Generate bill
        generateBill(patient);
    }

    // ========================================================
    // SEARCH PATIENT
    // ========================================================

    void searchPatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        patient->display();
    }

    // ========================================================
    // DISPLAY ALL PATIENTS
    // ========================================================

    void displayPatients()
    {
        if (patients.empty())
        {
            cout << "\nNo patient records available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================\n";
        cout << "                       PATIENT RECORDS\n";
        cout << "====================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(22) << "Name"
             << setw(6) << "Age"
             << setw(15) << "Disease"
             << setw(12) << "Doctor"
             << setw(12) << "Status"
             << setw(8) << "Priority"
             << '\n';

        cout << string(83, '-') << '\n';

        for (const auto& patient : patients)
        {
            cout << left
                 << setw(8) << patient.getId()
                 << setw(22) << patient.getName()
                 << setw(6) << patient.getAge()
                 << setw(15) << patient.getDisease();

            if (patient.getDoctorId() == -1)
                cout << setw(12) << "None";
            else
                cout << setw(12) << patient.getDoctorId();

            cout << setw(12)
                 << (patient.isAdmitted()
                     ? "Admitted"
                     : "Discharged");

            cout << setw(8)
                 << patient.getPriority()
                 << '\n';
        }

        cout << "====================================================================\n";
    }

    // ========================================================
    // GENERATE BILL
    // ========================================================

    void generateBill(Patient* patient)
    {
        double bedCharges = 0;

        if (!patient->getAdmissionDate().empty())
        {
            string dischargeDate =
                patient->getDischargeDate();

            int days =
                daysBetween(
                    patient->getAdmissionDate(),
                    dischargeDate
                );

            bedCharges =
                days * BED_CHARGE_PER_DAY;
        }

        Bill bill(
            patient->getId(),
            REGISTRATION_FEE,
            CONSULTATION_FEE,
            bedCharges
        );

        bill.display();

        saveBill(bill);
    }

    // ========================================================
    // APPOINTMENT QUEUE
    // ========================================================

    void addAppointment()
    {
        int patientId;
        int doctorId;
        string date;
        string time;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        if (findPatient(patientId) == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        displayDoctors();

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;

        if (findDoctor(doctorId) == nullptr)
        {
            cout << "Doctor not found.\n";
            return;
        }

        clearInput();

        cout << "Enter Appointment Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Appointment Time (HH:MM): ";
        getline(cin, time);

        Patient* patient =
            findPatient(patientId);

        Appointment appointment;

        appointment.patientId = patientId;
        appointment.doctorId = doctorId;
        appointment.date = date;
        appointment.time = time;
        appointment.priority =
            patient->getPriority();

        appointmentQueue.push(appointment);

        saveAppointment(appointment);

        cout << "\nAppointment added successfully!\n";
    }

    // ========================================================
    // SAVE APPOINTMENT
    // ========================================================

    void saveAppointment(
        const Appointment& appointment)
    {
        ofstream file(
            APPOINTMENT_FILE,
            ios::app
        );

        file << appointment.patientId << "|"
             << appointment.doctorId << "|"
             << appointment.date << "|"
             << appointment.time << "|"
             << appointment.priority
             << '\n';

        file.close();
    }

    // ========================================================
    // LOAD APPOINTMENTS
    // ========================================================

    void loadAppointments()
    {
        ifstream file(APPOINTMENT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string patientStr;
            string doctorStr;
            string date;
            string time;
            string priorityStr;

            getline(ss, patientStr, '|');
            getline(ss, doctorStr, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, priorityStr, '|');

            Appointment appointment;

            appointment.patientId =
                stoi(patientStr);

            appointment.doctorId =
                stoi(doctorStr);

            appointment.date = date;
            appointment.time = time;

            appointment.priority =
                stoi(priorityStr);

            appointmentQueue.push(appointment);
        }

        file.close();
    }

    // ========================================================
    // VIEW APPOINTMENT QUEUE
    // ========================================================

    void displayAppointmentQueue()
    {
        if (appointmentQueue.empty())
        {
            cout << "\nNo appointments in queue.\n";
            return;
        }

        // Copy queue so original remains unchanged
        auto temp = appointmentQueue;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                 APPOINTMENT QUEUE\n";
        cout << "============================================================\n";

        cout << left
             << setw(12) << "Patient ID"
             << setw(12) << "Doctor ID"
             << setw(15) << "Date"
             << setw(10) << "Time"
             << setw(10) << "Priority"
             << '\n';

        cout << string(59, '-') << '\n';

        while (!temp.empty())
        {
            Appointment appointment =
                temp.top();

            temp.pop();

            cout << left
                 << setw(12)
                 << appointment.patientId
                 << setw(12)
                 << appointment.doctorId
                 << setw(15)
                 << appointment.date
                 << setw(10)
                 << appointment.time
                 << setw(10)
                 << appointment.priority
                 << '\n';
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // SERVE NEXT APPOINTMENT
    // ========================================================

    void serveNextAppointment()
    {
        if (appointmentQueue.empty())
        {
            cout << "\nNo appointments waiting.\n";
            return;
        }

        Appointment next =
            appointmentQueue.top();

        appointmentQueue.pop();

        cout << "\n============================================\n";
        cout << "          NEXT PATIENT TO SERVE\n";
        cout << "============================================\n";

        cout << "Patient ID : "
             << next.patientId << '\n';

        cout << "Doctor ID  : "
             << next.doctorId << '\n';

        cout << "Date       : "
             << next.date << '\n';

        cout << "Time       : "
             << next.time << '\n';

        cout << "Priority   : "
             << next.priority << '\n';

        cout << "============================================\n";

        cout << "Patient served and removed from queue.\n";
    }

    // ========================================================
    // EMERGENCY PRIORITY LIST
    // ========================================================

    void emergencyPriorityList()
    {
        vector<Patient> emergencyPatients;

        for (const auto& patient : patients)
        {
            emergencyPatients.push_back(patient);
        }

        sort(
            emergencyPatients.begin(),
            emergencyPatients.end(),
            [](const Patient& a, const Patient& b)
            {
                return a.getPriority() <
                       b.getPriority();
            }
        );

        cout << "\n";
        cout << "============================================================\n";
        cout << "              EMERGENCY PRIORITY SYSTEM\n";
        cout << "============================================================\n";

        cout << left
             << setw(10) << "Priority"
             << setw(12) << "Patient ID"
             << setw(25) << "Name"
             << setw(20) << "Disease"
             << setw(15) << "Status"
             << '\n';

        cout << string(82, '-') << '\n';

        for (const auto& patient :
             emergencyPatients)
        {
            cout << left
                 << setw(10)
                 << patient.getPriority()
                 << setw(12)
                 << patient.getId()
                 << setw(25)
                 << patient.getName()
                 << setw(20)
                 << patient.getDisease()
                 << setw(15)
                 << (patient.isAdmitted()
                     ? "Admitted"
                     : "Waiting")
                 << '\n';
        }

        cout << "============================================================\n";

        cout << "\nPriority Meaning:\n";
        cout << "1 = Critical Emergency\n";
        cout << "2 = Serious\n";
        cout << "3 = Moderate\n";
        cout << "4 = Mild\n";
        cout << "5 = Normal\n";
    }

    // ========================================================
    // ADMIN MENU
    // ========================================================

    void adminMenu()
    {
        string password;

        clearInput();

        cout << "\nEnter Admin Password: ";
        getline(cin, password);

        if (password != "hospital123")
        {
            cout << "Incorrect password.\n";
            return;
        }

        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "              HOSPITAL ADMIN PANEL\n";
            cout << "============================================\n";

            cout << "1. Display All Patients\n";
            cout << "2. Display Doctors\n";
            cout << "3. Search Patient\n";
            cout << "4. Appointment Queue\n";
            cout << "5. Emergency Priority List\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayPatients();
                    break;

                case 2:
                    displayDoctors();
                    break;

                case 3:
                    searchPatient();
                    break;

                case 4:
                    displayAppointmentQueue();
                    break;

                case 5:
                    emergencyPriorityList();
                    break;

                case 6:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadPatients();
        loadDoctors();
        loadAppointments();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "================================================\n";
            cout << "       HOSPITAL PATIENT MANAGEMENT SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Register Patient\n";
            cout << "2. Assign Doctor\n";
            cout << "3. Admit Patient\n";
            cout << "4. Discharge Patient\n";
            cout << "5. Search Patient\n";
            cout << "6. Display Patient Records\n";
            cout << "7. Display Doctors\n";
            cout << "8. Generate Patient Bill\n";
            cout << "9. Add Appointment\n";
            cout << "10. View Appointment Queue\n";
            cout << "11. Serve Next Appointment\n";
            cout << "12. Emergency Priority System\n";
            cout << "13. Admin Panel\n";
            cout << "14. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    registerPatient();
                    break;

                case 2:
                    assignDoctor();
                    break;

                case 3:
                    admitPatient();
                    break;

                case 4:
                    dischargePatient();
                    break;

                case 5:
                    searchPatient();
                    break;

                case 6:
                    displayPatients();
                    break;

                case 7:
                    displayDoctors();
                    break;

                case 8:
                {
                    int patientId;

                    cout << "\nEnter Patient ID: ";
                    cin >> patientId;

                    Patient* patient =
                        findPatient(patientId);

                    if (patient == nullptr)
                    {
                        cout << "Patient not found.\n";
                    }
                    else
                    {
                        generateBill(patient);
                    }

                    break;
                }

                case 9:
                    addAppointment();
                    break;

                case 10:
                    displayAppointmentQueue();
                    break;

                case 11:
                    serveNextAppointment();
                    break;

                case 12:
                    emergencyPriorityList();
                    break;

                case 13:
                    adminMenu();
                    break;

                case 14:
                    savePatients();
                    saveDoctors();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Hospital Management System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 14);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    Hospital hospital;

    hospital.run();

    return 0;
}