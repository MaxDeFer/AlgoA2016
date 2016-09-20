#include "Ligne.h"

Ligne::Ligne(const std::vector<std::string>& ligne_gtfs)
{

}

CategorieBus Ligne::couleurToCategorie(std::string couleur) {
}

std::string Ligne::categorieToString(CategorieBus c) {
}

CategorieBus Ligne::getCategorie() const {
}

void Ligne::setCategorie(CategorieBus categorie) {
}

std::pair<std::string, std::string> Ligne::getDestinations() const {
}

unsigned int Ligne::getId() const {
}

void Ligne::setId(unsigned int id) {
}

const std::string& Ligne::getNumero() const {
}

void Ligne::setNumero(const std::string& numero) {
}

const std::vector<Voyage*>& Ligne::getVoyages() const {
}

void Ligne::setVoyages(const std::vector<Voyage*>& voyages) {
}

void Ligne::addVoyage(Voyage* ptr_voyage) {
}

const std::string& Ligne::getDescription() const {
}

void Ligne::setDescription(const std::string& description) {
}
/*
 * ligne.cpp
 *
 *  Created on: 2016-09-19
 *      Author: etudiant
 */




