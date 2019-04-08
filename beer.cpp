//
//  beer.cpp
//  Final Project
//
//  Created by Michael Lucky on 4/4/19.
//  Copyright © 2019 Michael Lucky. All rights reserved.
//

#include "beer.hpp"

#include <iostream>

using namespace std;

Hash::Hash(int maxSize){
    if (maxSize > 0) {
        TableSize = maxSize;
    }
    //alloc = 0;
    table = new recipe * [TableSize];
    //alloc++;
    for (int i = 0; i < TableSize; i++) {
        table[i] = nullptr;
    }
    currSize = 0;
    //dealloc = 0;
}
Hash::~Hash(void){
    for (int i = 0; i < TableSize; i++) {
        if (table[i]) {
            recipe * pointer = table[i], * previous = nullptr;
            while (pointer) {
                previous = pointer;
                //cout << previous->ikey << " deleted" << endl;
                delete previous;
                pointer = pointer->next;
                //dealloc++;
            }
        }
    }
    delete [] table;
    //dealloc++;
    /*    if (!(alloc - dealloc)) {
     cout << "All memory freed" << endl;
     }else{
     cout << "memory leak" << endl;
     }
     */
}
int Hash::hash(string key){
    int hashValue = 5381 ;
    size_t length = key.length();
    for (size_t i= 0; i < length; i++){
        hashValue=((hashValue << 5)+hashValue) + key[i];
    }
    hashValue %= TableSize;
    return hashValue;
}
void Hash::insert(recipe beerRecipe){
    int index = hash(beerRecipe.name);
    if (index >= 0 && index < TableSize) {
        
        if (!table[index]) {
            table[index] = new recipe;
            //alloc++;
            table[index]->next = nullptr;
            table[index]->name = beerRecipe.name;
            table[index]->brewer = beerRecipe.brewer;
            table[index]->equipment = beerRecipe.equipment;
            table[index]->style = beerRecipe.style;
            table[index]->category = beerRecipe.category;
            table[index]->description = beerRecipe.description;
            table[index]->minOG = beerRecipe.minOG;
            table[index]->maxOG = beerRecipe.maxOG;
            table[index]->minFG = beerRecipe.minFG;
            table[index]->maxFG = beerRecipe.maxFG;
            table[index]->minIBU = beerRecipe.minIBU;
            table[index]->maxIBU = beerRecipe.maxIBU;
            table[index]->minCarb = beerRecipe.minCarb;
            table[index]->maxCarb = beerRecipe.maxCarb;
            table[index]->minABV = beerRecipe.minABV;
            table[index]->maxABV = beerRecipe.maxABV;
            table[index]->grainWeight = beerRecipe.grainWeight;
            table[index]->grainTemp = beerRecipe.grainTemp;
            table[index]->boilTemp = beerRecipe.boilTemp;
            table[index]->PH = beerRecipe.PH;
            table[index]->age = beerRecipe.age;
            table[index]->OGmessured = beerRecipe.OGmessured;
            table[index]->FGmessured = beerRecipe.FGmessured;
            table[index]->ingredients = beerRecipe.ingredients;
            //cout << key << " inserted" << endl;
        }else{
            recipe * pointer = table[index]->next, * chaser = table[index];
            while (pointer) {
                chaser = pointer;
                pointer = pointer->next;
            }
            chaser->next = new recipe;
            alloc++;
            chaser->next->next = nullptr;
            chaser->next->name = beerRecipe.name;
            chaser->next->brewer = beerRecipe.brewer;
            chaser->next->equipment = beerRecipe.equipment;
            chaser->next->style = beerRecipe.style;
            chaser->next->category = beerRecipe.category;
            chaser->next->description = beerRecipe.description;
            chaser->next->minOG = beerRecipe.minOG;
            chaser->next->maxOG = beerRecipe.maxOG;
            chaser->next->minFG = beerRecipe.minFG;
            chaser->next->maxFG = beerRecipe.maxFG;
            chaser->next->minIBU = beerRecipe.minIBU;
            chaser->next->maxIBU = beerRecipe.maxIBU;
            chaser->next->minCarb = beerRecipe.minCarb;
            chaser->next->maxCarb = beerRecipe.maxCarb;
            chaser->next->minABV = beerRecipe.minABV;
            chaser->next->maxABV = beerRecipe.maxABV;
            chaser->next->grainWeight = beerRecipe.grainWeight;
            chaser->next->grainTemp = beerRecipe.grainTemp;
            chaser->next->boilTemp = beerRecipe.boilTemp;
            chaser->next->PH = beerRecipe.PH;
            chaser->next->age = beerRecipe.age;
            chaser->next->OGmessured = beerRecipe.OGmessured;
            chaser->next->FGmessured = beerRecipe.FGmessured;
            chaser->next->ingredients = beerRecipe.ingredients;
            //cout << key << " chained" << endl;
        }
        currSize++;
    }
}
recipe * Hash::search(string key, string parameter){
    int s = 0;
    if (parameter == "name" || parameter == "Name") {
        s = 1;
    }else if (parameter == "brewer" || parameter == "Brewer"){
        s = 2;
    }else if (parameter == "equipment" || parameter == "Equipment"){
        s = 3;
    }else if (parameter == "style" || parameter == "Style"){
        s = 4;
    }else if (parameter == "category" || parameter == "Category"){
        s = 5;
    }else if (parameter == "description" || parameter == "Description"){
        s = 6;
    }else if (parameter == "ingrediant" || parameter == "Ingrediant" || parameter == "ingrediants" || parameter == "Ingrediants"){
        s = 7;
    }
    switch (s) {
        case 1:{
            int index = hash(key);
            if (index >= 0 && index < TableSize) {
                recipe * pointer = table[index];
                while (pointer) {
                    if (pointer->name == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 2:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->brewer == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 3:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->equipment == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 4:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->style == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 5:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->category == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 6:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    if (pointer->description == key) {
                        return pointer;
                    }else{
                        pointer = pointer->next;
                    }
                }
            }
            break;
        }
        case 7:{
            for (int i = 0; i < TableSize; i++) {
                recipe * pointer = table[i];
                while (pointer) {
                    for (int i = 0; i < pointer->ingredients.size(); i++) {
                        if (pointer->ingredients[i] == key) {
                            return pointer;
                        }
                    }
                    pointer = pointer->next;
                }
            }
            break;
        }
        default:
            cout << "not a vaild parameter" << endl;
            break;
    }
    return nullptr;
}
recipe * Hash::search(double key, string parameter){
    return nullptr;
}
void Hash::del(string key){
    int index = hash(key);
    if (index >= 0 && index < TableSize) {
        if (table[index]->name == key) {
            recipe * temp = table[index];
            table[index] = table[index]->next;
            delete temp;
            //dealloc++;
            //currSize--;
        }else{
            recipe * pointer = table[index]->next, * chaser = table[index];
            while (pointer) {
                if (pointer->name == key) {
                    chaser->next = pointer->next;
                    delete pointer;
                    //dealloc++;
                    //currSize--;
                    break;
                }
                chaser = pointer;
                pointer = pointer->next;
            }
        }
    }
}
void Hash::print(){
    for (int i = 0; i < TableSize; i++) {
        recipe * pointer = table[i];
        cout << i << ": ";
        while (pointer) {
            cout << pointer->name << ":" << endl;
            pointer = pointer->next;
        }
        cout << endl;
    }
}
