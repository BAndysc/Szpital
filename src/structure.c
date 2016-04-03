#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "disease.h"
#include "patient.h"

/**
 * Disease list
 */

static DiseaseList* newDiseaseList() {
    DiseaseList* list = calloc(1, sizeof(DiseaseList));
    list->first = calloc(1, sizeof(DiseaseNode));
    list->last = list->first;
    return list;
}

static DiseaseNode* getDiseaseNodeForward(DiseaseList* list, int index) {
    DiseaseNode* node = list->first->next;

    while (index-- > 0)
        node = node->next;

    return node;
}

static DiseaseNode* getDiseaseNodeBackwards(DiseaseList* list, int index) {
    DiseaseNode* node = list->last;

    while (index-- > 0)
        node = node->prev;

    return node;
}

static DiseaseNode* getDiseaseNode(DiseaseList* list, int index) {
    if (index >= list->size)
        return NULL;

    if (index > list->size/2)
        return getDiseaseNodeBackwards(list, list->size-index-1);
    else
        return getDiseaseNodeForward(list, index);
}

static void changeDiseaseNodePointers(DiseaseNode* node) {
    node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
}

static void removeDisease(DiseaseList* list, int index) {
    DiseaseNode* nodeToRemove = getDiseaseNode(list, index);
    if (!nodeToRemove)
        return;

    changeDiseaseNodePointers(nodeToRemove);

    Diseases.free(nodeToRemove->value);
    free(nodeToRemove);

    list->size--;
}

static void freeDiseaseList(DiseaseList* list) {
    while (list->size > 0)
        removeDisease(list, 0);
    free(list->first);
    free(list);
}

static void pushDisease(DiseaseList* list, Disease* disease) {
    DiseaseNode* node = malloc(sizeof(DiseaseNode));

    node->value = disease;
    node->prev = list->last;
    node->next = NULL;

    list->last->next = node;
    list->last = node;
    list->size++;
}

static Disease* getDisease(DiseaseList* list, int index) {
    if (index < 0 || index >= list->size)
        return NULL;

    return getDiseaseNode(list, index)->value;
}


static Disease* getLastDisease(DiseaseList* list) {
    return list->last->value;
}

const struct diseaseLists DiseaseLists = {
    .new = newDiseaseList,
    .free = freeDiseaseList,
    .push = pushDisease,
    .remove = removeDisease,
    .get = getDisease,
    .getLast = getLastDisease,
};


/*
 * PATIENT LIST
 */
static void removePatient(PatientList* list, int index);

static PatientList* newPatientList() {
    PatientList* list = malloc(sizeof(PatientList));

    list->first = calloc(1, sizeof(PatientNode));
    list->size = 0;
    list->last = list->first;

    return list;
}


static void freePatientList(PatientList* list) {
    while (list->size > 0)
        removePatient(list, 0);

    free(list->first);
    free(list);
}


static PatientNode* getPatientNode(PatientList* list, int index) {
    if (index >= list->size)
        return NULL;

    PatientNode* node = list->first->next;

    while (index-- > 0)
        node = node->next;

    return node;
}


static PatientNode* getPatientNodeByName(PatientList* list, const char* name) {
    PatientNode* node = list->first->next;

    while (node) {
        if (strcmp(node->value->name, name) == 0)
            return node;

        node = node->next;
    }

    return NULL;
}

static void changePatientNodePointers(PatientNode* node) {
    node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
}

static void removePatient(PatientList* list, int index) {
    PatientNode* nodeToRemove = getPatientNode(list, index);
    if (!nodeToRemove)
        return;

    changePatientNodePointers(nodeToRemove);

    Patients.free(nodeToRemove->value);
    free(nodeToRemove);

    list->size--;
}

static Patient* getPatient(PatientList* list, int index) {
    if (index >= list->size)
        return NULL;

    return getPatientNode(list, index)->value;
}

static Patient* getPatientByName(PatientList* list, char const* name) {
    PatientNode* patientNode = getPatientNodeByName(list, name);

    if (!patientNode)
        return NULL;

    return patientNode->value;
}

static void pushPatient(PatientList* list, Patient* patient) {
    PatientNode* node = malloc(sizeof(PatientNode));

    node->value = patient;
    node->prev = list->last;
    node->next = NULL;

    list->last->next = node;
    list->last = node;
    list->size++;
}


const struct patientLists PatientLists = {
        .new = newPatientList,
        .free = freePatientList,
        .push = pushPatient,
        .remove = removePatient,
        .getByName = getPatientByName
};
