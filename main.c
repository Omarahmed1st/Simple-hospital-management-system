#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOODTYPESMAXSIZE 8 //number of blood type
#define _CRT_SECURE_NO_WARNINGS

struct patient {

    int p_ID;
    char p_F_Name[20];
    char p_L_Name[20];
    char type[20];
    char service[50];
    char address[150];
    int age;
    char sex[10];
    char blood_type[5];
    char disease_description[100];
    int specialist_room_number;

};

typedef struct{
    char name[50];
    int numberOfrooms;
    int numberOfbedsPerRoom;
    char service[30];
    int totalNumberOfbeds;
    int bedCounter;

}Deperatment;

typedef struct{
    char type[5]; // A+ A- B+ B- AB+ AB-
    float quantity; // amount in litres
} BloodType;

BloodType bloodtypes[BLOODTYPESMAXSIZE];
int bloodtypesCount = 0;

Deperatment emergency;
Deperatment newborn;
void create_emergency_departement();
struct patient patients[100];

int patients_count=0;
int patients_counter =1;

Deperatment deperatments[20];
int deperatments_count = 0;

void add_deperatments();

Deperatment create_deperatment(char* name, char* service, int numberOfbedsPerRoom, int numberOfRooms);
void add_patient();
void Track_intensive_care();
void Track_baby_incubators();
void Track_Blood_Type();
int Hospital_capacity();
void create_blood_types();
void edit_patient();
int get_patient_index(int id);
void list_patients();

int main() {
    create_emergency_departement();
    add_deperatments();
    create_blood_types();
    create_newborn_departement();

// main menu choices
    int choice;
    do {
        printf("\n\t\t\t\t\t\t----------------------\n");
        printf("\t\t\t\t\t\t*******Welcome*******\n");
        printf("\t\t\t\t\t\t----------------------\n\n\n");
        printf("1. Add Patient(s)\n");
        printf("2. Track intensive Care\n");
        printf("3. Track blood types\n");
        printf("4. Track new born\n");
        printf("5. Hospital capacity\n");
        printf("6. list patient\n");
        printf("7. Edit patient\n");
        printf("8. Delete patient\n");
        printf("9. Exit\n");

        printf("Choice : \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            {
                int patientsNum;
                printf("Please enter the number of patients you want to add : \n");
                scanf("%d", &patientsNum);

                for(int i = 0; i < patientsNum; i++){
                    add_patient();
                }

            }
            break;
        case 2:
            Track_intensive_care();
            break;

        case 3:
            Track_Blood_Type();
            break;
         case 4:
            Track_baby_incubators();
            break;

            case 5:
            Hospital_capacity();
            break;
             case 6:
            list_patients();
            break;
        case 7:
            edit_patient();
            break;
        case 8:
            delete_patient();
            break;
        case 9:
            break;

        default:
            printf("Invalid choice, try again\n");
            break;
        }

    }while(choice != 9);

    printf("Thank you for using our system\n");
    return 0;

}


//HERE WE ADD PATIENTS

void add_patient() {
    struct patient p;
    int blood_choice, i;

    printf("Enter patient first name please: \n");
    getchar();
    gets(p.p_F_Name);

    printf("Enter patient last name please: \n");
    gets(p.p_L_Name);

    printf("Enter age: \n");
    scanf("%d", &p.age);

    getchar();
    printf("Enter sex: \n");

    gets( p.sex);

    printf("Enter address: \n");
    gets( p.address);

    printf("Blood types : \n");
    for(i = 0; i < bloodtypesCount; i++){
        printf("%d. %s type\n", i+1, bloodtypes[i]);
    }
    printf("choice: ");
    scanf("%d", &blood_choice);

    if(bloodtypes[blood_choice-1].quantity > 0.0f){
        strcpy(p.blood_type, bloodtypes[blood_choice-1].type);
        bloodtypes[blood_choice-1].quantity -= 1.0;
    }
    else{
        printf("blood type %s is not available currently, try again later\n", bloodtypes[blood_choice-1].type);
        return;
    }

    getchar();
    printf("Enter patient type (ordinary, emergency, or new-born): \n");
    gets( p.type);


    if(strcmp(p.type, "ordinary") == 0) {

        int choice, i;
        printf("Please choose service number : \n");
        for(i = 0; i < deperatments_count; i++){
            printf("%d. %s service\n",i + 1, deperatments[i].service);
        }
        printf("Choice : ");
        scanf("%d", &choice);

        strcpy(p.service, deperatments[ choice- 1].service);

        printf("Enter disease description: \n");
        getchar();
        gets( p.disease_description);

        deperatments[choice - 1].bedCounter++;
        p.specialist_room_number=deperatments[i - 1].bedCounter/deperatments[i - 1].numberOfbedsPerRoom;

        printf("\nPatient record added successfully!\n");

     } else if(strcmp(p.type, "emergency") == 0) {
         // save patient record to file or database
         emergency.bedCounter++;
         strcpy(p.service,emergency.service);
          printf("Enter disease description: \n");
        getchar();
        gets( p.disease_description);
         printf("\nPatient record added successfully!\n");

     } else if(strcmp(p.type, "new-born") == 0) {
         newborn.bedCounter++;
         strcpy(p.service,newborn.service);
          printf("Enter disease description: \n");
        getchar();
        gets( p.disease_description);
         printf("\nPatient record added successfully!\n");


     } else {
         printf("\nInvalid patient type entered. Please try again.\n");
         add_patient();
     }
    p.p_ID = patients_counter;
    patients_counter++;

    patients[patients_count]=p;
    patients_count++;
}


void Track_intensive_care() {
int avilablety=emergency.totalNumberOfbeds-emergency.bedCounter;
for(int i=0 ; i< patients_count; i++){
 if(strcmp(patients[i].service,emergency.service)==0)
 {
     printf("Data of patient:\n");
     printf("patient first name: %s \n",patients[i].p_F_Name);
     printf("patient last name: %s \n",patients[i].p_L_Name);
     printf("patient sex: %s \n",patients[i].sex);
     printf("patient age: %d \n",patients[i].age);
     printf("patient address: %s \n",patients[i].address);
     printf("patient blood type: %s \n",patients[i].blood_type);

 }
}
printf("\nAvilabale number of beds = %d bed\n", avilablety);
}


int Hospital_capacity(){
	int department_code;
	int i;
	printf("Choose the number corresponding to the department to obtain its capacity:\n");
	for(i = 0; i < deperatments_count; i++){
        printf("%d : %s Department\n", i + 1, deperatments[i].name);
	}
    getchar();
    printf("Choice : ");
	scanf("%d", &department_code);

	printf("Maximum capacity of %s deperatment is %d, Current number of patients is %d", deperatments[department_code-1].name,
         deperatments[department_code-1].totalNumberOfbeds, deperatments[department_code-1].bedCounter);
}

void edit_patient(){
    int id, menu_choice;

    printf("Please enter the patient id : ");
    scanf("%d", &id);

    int index = get_patient_index(id);

    if(index == -1){
        printf("%d is an invalid patient id, try again\n", id);
        return;
    }

    do{
        printf("Please change attribute you want to change :\n");
        printf("1. first name\n");
        printf("2. last name\n");
        printf("3. age\n");
        printf("4. address\n");
        printf("5. sex\n");
        printf("6. go back\n");

        printf("choice : ");
        scanf("%d", &menu_choice);

        switch(menu_choice){
        case 1:
            getchar();
            printf("Please enter new first name :");
            gets(patients[index].p_F_Name);

            printf("Patient's first name updated to %s successfully\n", patients[index].p_F_Name);
            break;
        case 2:
            getchar();
            printf("Please enter new last name :");
            gets(patients[index].p_L_Name);

            printf("Patient's last name updated to %s successfully\n", patients[index].p_L_Name);
            break;
        case 3:
            printf("Please enter new age :");
            scanf("%d", &patients[index].age);

            printf("Patient's age updated to %d successfully\n", patients[index].age);
            break;
        case 4:
            getchar();
            printf("Please enter new address :");
            gets(patients[index].address);

            printf("Patient's address updated to %s successfully\n", patients[index].address);
            break;
             case 5:
            getchar();
            printf("Please enter new sex type :");
            gets(patients[index].sex);

            printf("Patient's sex type updated to %s successfully\n", patients[index].sex);
            break;
        case 6:
            break;
        default:
            printf("Invalid choice try again\n");
            break;
        }

    } while(menu_choice != 6);

}

int get_patient_index(int id){  // To search about patient
    for(int i = 0;i < patients_count; i++){
        if(patients[i].p_ID == id){
            return i;
        }
    }
    return -1;
}

void list_patients(){
    int id;

    printf("Enter patient Id: \n");
    scanf("%d",&id);

    int index = get_patient_index(id);
    if(index == -1){

        printf("%d is an invalid patient id, try again\n", id);
        return;
    }
    printf("Data of the pateint:\n");
    printf("patient first name: %s\n",patients[index].p_F_Name);
    printf("patient last name: %s\n",patients[index].p_L_Name);
    printf("patient age: %d\n",patients[index].age);
    printf("patient address: %s\n",patients[index].address);
    printf("patient service: %s\n",patients[index].service);
    printf("patient sex: %s\n",patients[index].sex);
    printf("patient disease description: %s\n",patients[index].disease_description);
    printf("patient blood type: %s\n",patients[index].blood_type);
    printf("patient type of patient: %s\n",patients[index].type);
}

void add_deperatments(){


    deperatments[deperatments_count] = create_deperatment("Cardiology", "heart", 15, 5);
    deperatments_count++;

    deperatments[deperatments_count] = create_deperatment("Orthopedics", "Bone Fracture", 7, 5);
    deperatments_count++;

    deperatments[deperatments_count] = create_deperatment("ENT", "ear Infection", 10, 5);
    deperatments_count++;

    deperatments[deperatments_count] = create_deperatment("Neruo", "Brain & Nerves", 5, 6);
    deperatments_count++;

    deperatments[deperatments_count] = create_deperatment("oncology", "cancer", 10, 5);
    deperatments_count++;

    deperatments[deperatments_count] = create_deperatment("Psychiatry ", "Mental Health Issues", 10, 3);
    deperatments_count++;

}

Deperatment create_deperatment(char* name, char* service, int numberOfbedsPerRoom, int numberOfRooms){
    Deperatment d;
    strcpy(d.name, name);
    strcpy(d.service, service);
    d.numberOfrooms = numberOfRooms;
    d.numberOfbedsPerRoom = numberOfbedsPerRoom;

    d.totalNumberOfbeds = numberOfRooms * numberOfbedsPerRoom;
    d.bedCounter = 0;

    return d;

}

void Track_Blood_Type(){
    for(int i = 0; i < bloodtypesCount; i++){
        printf("type : %s\n", bloodtypes[i].type);
        printf("quantity : %.2f litres\n\n", bloodtypes[i].quantity);
    }
}

void create_blood_types(){

    strcpy(bloodtypes[bloodtypesCount].type, "A+");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;
    strcpy(bloodtypes[bloodtypesCount].type, "A-");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;

    strcpy(bloodtypes[bloodtypesCount].type, "B+");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;
    strcpy(bloodtypes[bloodtypesCount].type, "B-");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;

    strcpy(bloodtypes[bloodtypesCount].type, "O+");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;
    strcpy(bloodtypes[bloodtypesCount].type, "O-");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;

    strcpy(bloodtypes[bloodtypesCount].type, "AB+");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;
    strcpy(bloodtypes[bloodtypesCount].type, "AB-");
    bloodtypes[bloodtypesCount].quantity = 10.0f;
    bloodtypesCount++;
}


void create_emergency_departement(){
    emergency.bedCounter=0;
    emergency.numberOfbedsPerRoom=15;
    emergency.numberOfrooms=5;
    emergency.totalNumberOfbeds=emergency.numberOfrooms*emergency.numberOfbedsPerRoom;
    strcpy(emergency.name,"IC");
    strcpy(emergency.service,"E_S");
    }
void Track_baby_incubators(){

    int avilablety=newborn.totalNumberOfbeds-newborn.bedCounter;
for(int i=0 ; i< patients_count; i++){
 if(strcmp(patients[i].service,newborn.service)==0)
 {
     printf("patient first name: %s \n",patients[i].p_F_Name);
     printf("patient last name: %s \n",patients[i].p_L_Name);
     printf("patient sex: %s \n",patients[i].sex);
     printf("patient age: %d \n",patients[i].age);
     printf("patient address: %s \n",patients[i].address);

 }
}
printf("Avilabale number of beds = %d", avilablety);
}


void create_newborn_departement(){
    newborn.bedCounter=0;
    newborn.numberOfbedsPerRoom=5;
    newborn.numberOfrooms=5;
    newborn.totalNumberOfbeds=newborn.numberOfrooms*newborn.numberOfbedsPerRoom;
    strcpy(newborn.name,"NEW_BORN");
    strcpy(newborn.service,"E_S");
     strcpy(newborn.service,"N_B");
    }
void delete_patient(){
    int id = 0;
    printf("enter patient id : ");
    scanf("%d", &id);

    int index = get_patient_index(id);
    if(index == -1){
        printf("%d is an invalid patient id, try again", id);
    }

    for(int i = index; i < patients_count - 1; i++){
        patients[i] = patients[i + 1];
    }
    patients_count--;
}


