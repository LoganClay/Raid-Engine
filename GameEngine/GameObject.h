#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hitbox.h"
#include "Render.h"

using namespace sf;


class GameObject {
	public:
		string spriteFile;
		//coordinates of object
		shared_ptr<int> xPos, yPos;
		//Pixel dimensions of the individual sprites
		shared_ptr<int> spriteH, spriteW;
		//Amount of sprites in the dimensions of the sheet
		int unitsH, unitsW;

		Hitbox* hitbox;
		
		Render* render;
		Render::Node *node;
		Sprite sprite;
		Texture texture;
		
		int nodeNum;
		
		void fillAnimation(int array[60][2], int pX, int pY, int start, int length) {
			for (int i = start; i < start + length; i++) {
				for (int x = 0; x < 2; x++) {
					switch (x){
						case 0:
							array[i][x] = pX;
							break;
						case 1:
							array[i][x] = pY;
							break;
					}	
				}
				cout << i << ": " << array[i][0] << ", " << array[i][1] << endl;
			}
		}
		void createStillAnimation(int array[60][2], int pX, int pY) {
			for (int i = 0; i < 60; i++) {
				array[i][0] = pX;
				array[i][1] = pY;
			}
		}
		void SetAnimation(int n) { this->node->getAnimation()->setAnimation(n); }
};
class ObjectList {
public:
	class Node{
	public:
		GameObject* object;
		Node* next;
		Node(GameObject* object) {
			this -> object = object;
			this -> next = NULL;
		}
		void setNext(Node* node) { this -> next = node; }
	};
	int listSize;

	Node* first;
	Node* last;

	ObjectList() {
		listSize = 0;
		first = NULL;
		last = NULL;
	}

	Node* addObject(GameObject* object) {
		if (listSize == 0) {
			first = new Node(object);
			last = first;
			listSize++;
			return first;
		}
		else {
			Node* new_node = new Node(object);
			last->setNext(new_node);
			last = new_node;
			listSize++;
			return last;
		}
	}

	void removeObject(Node* node , Render* render) {
		if (listSize == 0) return;
		Node* temp = first;
		Node* temp2 = last;
		Node* temp3;
		for (int i = 0; i < listSize; i++) {
			if (temp == node && i == 0) {
				temp2 = temp->next;
				render->removeFromRender(node->object->node);
				delete temp;
				first = temp2;
				break;
			}
			else if (temp == node && node == last) {
				last = temp2;
				render->removeFromRender(node->object->node);
				delete temp;
				break;
			}
			else if (temp == node) {
				temp3 = temp->next;
				temp2->setNext(temp3);
				render->removeFromRender(node->object->node);
				delete temp;
				break;
			}
			temp2 = temp;
			temp = temp->next;
		}
		listSize--;
	}
	void truncateObjects(Node* node) {
		Node* temp = first;
		Node* temp2 = last;
		int sizeTemp = listSize;
		bool trunc = false;
		for (int i = 0; i < sizeTemp; i++) {
			if (trunc) {
				temp2 = temp->next;
				temp->object->render->removeFromRender(temp->object->node);
				delete temp;
				temp = temp2;
				listSize--;
			}
			else {
				temp2 = temp;
				temp = temp->next;
			}
			if (trunc == false && temp == node) {
				trunc = true;
				temp2->setNext(NULL);
				last = temp2;
			}
			cout << listSize << endl;
		}
		
	}
	void clearObjects() {
		Node* temp = first;
		Node* temp2 = last;
		for (int i = 0; i < listSize; i++) {
			temp2 = temp->next;
			temp->object->render->removeFromRender(temp->object->node);
			delete temp;
			temp = temp2;
		}
		first = NULL;
		last = NULL;
		listSize = 0;
	}
	Node* getIndex(int i) {
		if (i > listSize || i < 0)return first;
		Node* node = first;
		for (int x = 0; x < i; x++) {
			node = node->next;
		}
		return node;
	}
};
