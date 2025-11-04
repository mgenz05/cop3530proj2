#include <wx/wx.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"
using namespace std;

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

// "MyFrame" class used for first screen
class MyFrame : public wxFrame {
public:
    MyFrame();
    void onButtonClick(wxCommandEvent& event);
    void onDropdownClick(wxCommandEvent& event);
private:
    wxChoice* dropdown1;
    wxChoice* dropdown2;
    wxChoice* dropdown3;
};

// "MyFrame2" class used for second screen
class MyFrame2 : public wxFrame {
public:
    MyFrame2();
    void setOutput(wxString text1, wxString text2, wxString text3, wxString text4);
private:
    wxTextCtrl* txtbox1;
    wxTextCtrl* txtbox2;
    wxTextCtrl* txtbox3;
    wxTextCtrl* txtbox4;
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Auto Medicine Prescriber", wxDefaultPosition, wxSize(800, 700)) {
    // Sets up first screen for user selections
    wxPanel* panel = new wxPanel(this);
    // Stores dropdown options in each dropdown
    wxArrayString options1;
    options1.Add("Inhaler");
    options1.Add("Ointment");
    options1.Add("Cream");
    options1.Add("Injection");
    options1.Add("Syrup");
    options1.Add("Tablet");
    options1.Add("Capsule");
    options1.Add("Drops");
    wxArrayString options2;
    options2.Add("Prescription");
    options2.Add("Over-the-Counter");
    wxArrayString options3;
    options3.Add("Virus");
    options3.Add("Infection");
    options3.Add("Wound");
    options3.Add("Pain");
    options3.Add("Fungus");
    options3.Add("Diabetes");
    options3.Add("Depression");
    options3.Add("Fever");
    // Creates labels for dropdowns
    new wxStaticText(panel, wxID_ANY, "Dosage Form:", wxPoint(350, 420), wxDefaultSize);
    new wxStaticText(panel, wxID_ANY, "Classification:", wxPoint(350, 270), wxDefaultSize);
    new wxStaticText(panel, wxID_ANY, "Indication:", wxPoint(350, 120), wxDefaultSize);
    // Creates dropdowns
    dropdown1 = new wxChoice(panel, wxID_ANY, wxPoint(300,450), wxSize(200, 30), options1);
    dropdown2 = new wxChoice(panel, wxID_ANY, wxPoint(300,300), wxSize(200, 30), options2);
    dropdown3 = new wxChoice(panel, wxID_ANY, wxPoint(300,150), wxSize(200, 30), options3);
    // Creates Submit button
    wxButton* button = new wxButton(panel, wxID_ANY, "Submit", wxPoint(320, 525), wxSize(150, 55));
    dropdown1->Bind(wxEVT_CHOICE, &MyFrame::onDropdownClick, this);
    dropdown2->Bind(wxEVT_CHOICE, &MyFrame::onDropdownClick, this);
    dropdown3->Bind(wxEVT_CHOICE, &MyFrame::onDropdownClick, this);
    button->Bind(wxEVT_BUTTON, &MyFrame::onButtonClick, this);
}

MyFrame2::MyFrame2() : wxFrame(NULL, wxID_ANY, "Result Prescription", wxDefaultPosition, wxSize(1200, 700)) {
    // Sets up second screen to display results
    wxPanel* panel = new wxPanel(this);
    // Creates labels for textboxes
    new wxStaticText(panel, wxID_ANY, "Your Best Fit Medicine Is:", wxPoint(500, 125), wxDefaultSize);
    new wxStaticText(panel, wxID_ANY, "Its Category is:", wxPoint(200, 475), wxDefaultSize);
    new wxStaticText(panel, wxID_ANY, "Its Strength is:", wxPoint(500, 475), wxDefaultSize);
    new wxStaticText(panel, wxID_ANY, "Is Manufactured By:", wxPoint(800, 475), wxDefaultSize);
    // Creates textboxes
    txtbox1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500, 150), wxSize(200, 30), wxTE_READONLY);
    txtbox2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 500), wxSize(200, 30), wxTE_READONLY);
    txtbox3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500, 500), wxSize(200, 30), wxTE_READONLY);
    txtbox4 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(800, 500), wxSize(200, 30), wxTE_READONLY);
};

void MyFrame2::setOutput(wxString text1, wxString text2, wxString text3, wxString text4) {
    // Translates outputs to textboxes on second screen
    txtbox1->SetValue(text1);
    txtbox2->SetValue(text2);
    txtbox3->SetValue(text3);
    txtbox4->SetValue(text4);
}

void MyFrame::onDropdownClick(wxCommandEvent& event) {
    // Function to obtain input from dropdown selection
    wxChoice* c = wxDynamicCast(event.GetEventObject(), wxChoice);
    wxString choice = c->GetStringSelection();
}

void MyFrame::onButtonClick(wxCommandEvent& event) {
    // Obtains inputs from dropdowns
    wxString input1 = dropdown1->GetStringSelection();
    wxString input2 = dropdown2->GetStringSelection();
    wxString input3 = dropdown3->GetStringSelection();

    ifstream file("medicine_dataset.csv");
    if (!file.is_open()) {
        wxMessageBox("Failed to open medicine database file!", "Error", wxICON_ERROR);
        return;
    }
    
    //https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/
    unordered_map<string, vector<string>> medicineTable; // hashmap
    string line;

    while (getline(file, line)) { //for each line in the dataset read line by line
        stringstream streamofstring(line); // Create a stringstream from the line from dataset
        string segment;
        vector<string> medicine_data; // To store the split values of the current row of data

        while (getline(streamofstring, segment, ',')) { //split line into segments separated by the commas
            medicine_data.push_back(segment);
            // "Dextromet Antiseptic Tablet 287 mg AbbVie Inc. Diabetes Prescription"
        }

        vector<string> medicineCharacteristics; //contains characteristics of each medicine, minus the name
        for(int i = 1; i < medicine_data.size(); i++){
            medicineCharacteristics.push_back(medicine_data[i]);
        }
        //inserting into hashmap the name of each Medicine and a vector containing its characteristics
        medicineTable.insert({medicine_data[0], medicineCharacteristics});
    }
    file.close();

    // Create user selections vector
    vector<string> userSelections = {
        input1.ToStdString(),
        input2.ToStdString(),
        input3.ToStdString()
    };

    // Max timer start
    auto max_start = chrono::high_resolution_clock::now();

    // Run MaxHeap algorithm to find best match
    MaxHeap maxHeap;
    for (auto& entry : medicineTable) {
        int score = computeScore(entry, userSelections);
        maxHeap.insertItem(entry.first, score);
    }

    MedicineScore max_best = maxHeap.extractMax();

    // Max timer end
    auto max_stop = chrono::high_resolution_clock::now();

    // Max duration
    auto max_duration = chrono::duration_cast<chrono::microseconds>(max_stop - max_start);

    // Min timer start
    auto min_start = chrono::high_resolution_clock::now();

    // Run MinHeap algorithm to find best match
    MinHeap heap;
    for (auto& entry : medicineTable) {
        int score = computeScore(entry, userSelections);
        heap.insertItem(entry.first, score);
    }

    MedicineScore min_best = heap.extractMax();

    // Min timer end
    auto min_stop = chrono::high_resolution_clock::now();

    // Min duration
    auto min_duration = chrono::duration_cast<chrono::microseconds>(min_stop - min_start);

    // Get full medicine details from hash map
    string bestMedicineName = min_best.name;
    vector<string>& characteristics = medicineTable[bestMedicineName];

    // Characteristics 0 = Category, 2 = Strength, 3 = Manufacturer
    wxString medicineName = wxString(bestMedicineName);
    wxString category = wxString(characteristics[0]);
    wxString strength = wxString(characteristics[2]);
    wxString manufacturer = wxString(characteristics[3]);

    // Pop up for execution time
    wxString time = wxString::Format("Execution Time Comparison:\n\n Max Heap Time: %lld microseconds\n Min Heap Time: %lld microseconds\n", max_duration.count(), min_duration.count());
    wxMessageBox(time, "Execution Time", wxICON_INFORMATION | wxOK);

    MyFrame2* frame2 = new MyFrame2();
    frame2->setOutput(medicineName, category, strength, manufacturer);
    frame2->Show(true);
}


wxIMPLEMENT_APP(MyApp);
