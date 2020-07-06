/*
 * CContainer.cpp
 *
 *  Created on: 30 juin 2020
 *      Author: armand
 */

#include <CContainer.h>


/*CNode Section*/

CContainer::CNode::CNode() :
	m_pPrev {nullptr},
	m_pNext {nullptr},
	m_pElem {nullptr}
{
}

CContainer::CNode::CNode(CNode*pPrev,CNode*pNext,void*pElem) :
		m_pPrev(pPrev),
		m_pNext(pNext),
		m_pElem(pElem)
{
	if(pPrev) {pPrev->m_pNext = this;}
	if(pNext) {pNext->m_pPrev = this;}
}

CContainer::CNode::~CNode() {

	if(m_pPrev) {m_pPrev->m_pNext = m_pNext;}
	if(m_pNext) {m_pNext->m_pPrev = m_pPrev;}
}


/*CContainer Section*/


CContainer::CContainer() :
		m_pHead {nullptr},
		m_pTail {nullptr},
		m_nCard {0},
		m_pDeleteFunc {0}

{
	// TODO Auto-generated constructor stub
}

CContainer::CContainer(t_ptfV pDeleteFunc) :
		CContainer()
{
		m_pDeleteFunc = pDeleteFunc;

}

CContainer::~CContainer() {
	// TODO Auto-generated destructor stub

	while(m_pHead) {
		m_pTail = m_pHead;
		m_pHead = m_pHead->m_pNext;
		//m_pDeleteFunc(m_pTail->m_pElem);
		delete m_pTail;
		m_nCard--;
	}


}

void* CContainer::Pushback(void*pElem){

	if(m_nCard==0){
		assert(m_pHead==nullptr);
		assert(m_pTail==nullptr);
		m_pHead = m_pTail = new CNode(nullptr, nullptr, pElem);
	}
	else{
		m_pTail = new CNode(m_pTail, nullptr, pElem);
	}
	m_nCard++;
	assert(m_pTail->m_pElem==pElem);
	return pElem;
}

void* CContainer::Pushfront(void*pElem){

	if(m_nCard==0){
		assert(m_pHead==nullptr);
		assert(m_pTail==nullptr);
		m_pHead = m_pTail = new CNode(nullptr, nullptr, pElem);
	}
	else{
		m_pHead = new CNode(nullptr, m_pHead, pElem);
	}
	m_nCard++;
	assert(m_pHead->m_pElem==pElem);
	return pElem;
}

void* CContainer::Pushat(void*pElem, int nAt){

		assert(!this);
		assert(nAt>=0); assert(nAt<=m_nCard);

		if(nAt==0) return Pushfront(pElem);
		if(nAt==m_nCard) return Pushback(pElem);

		CNode* pScan;

		if(nAt<=m_nCard/2){
			pScan= m_pHead;

			while(nAt--){
				pScan = pScan->m_pNext;
			}
			pScan = new CNode(pScan->m_pPrev, pScan, pElem);
		}
		else{
			pScan=m_pTail;
			nAt=m_nCard-nAt;

			while(nAt--){
				pScan = pScan->m_pPrev;
			}
			pScan = new CNode(pScan, pScan->m_pNext, pElem);
		}
		m_nCard++;
		assert(pScan->m_pElem==pElem);
		return pScan->m_pElem;
}


void*CContainer::Getback(){
	assert(this!=NULL);
	assert(m_nCard!=0);
	return m_pTail->m_pElem;
}

void*CContainer::Getfront(){
	assert(this!=NULL);
	assert(m_nCard!=0);
	return m_pHead->m_pElem;
}

void*CContainer::Getat(int nAt){
	assert(this!=NULL);
	assert(m_nCard!=0);
	assert(nAt>=0); assert(nAt<m_nCard);

	if(nAt==0) return Getfront();
	if(nAt==m_nCard-1) return Getback();

	CNode*pScan;

	if(nAt<=m_nCard/2){
		pScan = m_pHead;
		while(nAt--){
			pScan = pScan->m_pNext;
		}
	}
	else{
		pScan = m_pTail;
		nAt = m_nCard-nAt-1;
		while(nAt--){
			pScan = pScan->m_pPrev;
		}
	}
	return pScan->m_pElem;
}


void*CContainer::Popback(){
	assert(this!=NULL);
	assert(m_nCard!=0);
	void*pElem = m_pTail->m_pElem;
	m_pDeleteFunc(m_pTail->m_pElem);
	delete m_pTail;
	m_nCard--;
	return pElem;
}

void*CContainer::Popfront(){
	assert(this!=NULL);
	assert(m_nCard!=0);
	void*pElem = m_pHead->m_pElem;
	m_pDeleteFunc(m_pHead->m_pElem);
	delete m_pHead;
	m_nCard--;
	return pElem;
}

void*CContainer::Popat(int nAt){
	assert(this!=NULL);
	assert(m_nCard!=0);
	assert(nAt>=0); assert(nAt<m_nCard);

	void*pElem;

	if(nAt==0) return Popfront();
	if(nAt==m_nCard-1) return Popback();

	CNode*pScan;

	if(nAt<=m_nCard/2){
		pScan=m_pHead;
		while(nAt--){
			pScan = pScan->m_pNext;
		}
	}
	else{
		pScan=m_pTail;
		nAt=m_nCard-nAt-1;
		while(nAt--){
			pScan = pScan->m_pPrev;
		}
	}
	pElem = pScan->m_pElem;
	m_pDeleteFunc(pScan->m_pElem);
	delete pScan;
	m_nCard--;
	return pElem;
}


void* CContainer::Parse(t_ptfVV pParseFunc, void*pParam){

	CNode * pScan {m_pHead};

	while(pScan){
		if(!pParseFunc(pScan->m_pElem, pParam)) return pScan->m_pElem;
			pScan = pScan->m_pNext;
	}

	return nullptr;
}

void*CContainer::ParseDelIf(t_ptfVV pParseFunc, void* pParam){
	assert(this!=NULL);
	assert(pParseFunc!=NULL);
	CNode*pScan = m_pHead;

	while (pScan != NULL) {
		if (!pParseFunc(pScan->m_pElem, pParam)) { pScan = DeleteByElem(this, pScan->m_pElem); }
		else{ pScan = pScan->m_pNext; }

	}

	return NULL;
}

CContainer::CNode*CContainer::DeleteByElem(CContainer* pCont, void*pElem){
	assert(pCont!=NULL);
	assert(pElem!=NULL);

	CNode*pScan;

	pScan = pCont->m_pHead;
	while((pScan!=NULL)&&(pScan->m_pElem!=pElem)){
		pScan = pScan->m_pNext;
	}
	if(pScan!=NULL){
		if(pScan==pCont->m_pHead){
			pCont->m_pHead = pScan->m_pNext;
			pCont->m_pDeleteFunc(pScan->m_pElem);
			delete pScan;
			pScan = pCont->m_pHead;

			if(pCont->m_nCard==1){
				pCont->m_pTail = pCont->m_pHead;
				assert(pCont->m_pHead==NULL);
			}
		}
		else if(pScan==pCont->m_pTail){
			pCont->m_pTail = pScan->m_pPrev;
			pCont->m_pDeleteFunc(pScan->m_pElem);
			delete pScan;
			pScan = nullptr;
		}
		else{
			pScan = pScan->m_pNext;
			pCont->m_pDeleteFunc(pScan->m_pPrev->m_pElem);
			delete pScan->m_pPrev;
		}
		pCont->m_nCard--;
	}

	return pScan;
}
void*CContainer::IntersectDelElemsIf(CContainer* pContB, t_ptfVVVV pIntersecFunc, t_ptfV pFunction, void* pParam){
	assert(this!=NULL);
	assert(pContB!=NULL);
	assert(pIntersecFunc!=NULL);

	CNode* pScanA, *pScanB;

	pScanA = m_pHead;

	while(pScanA) {
		pScanB = pContB->m_pHead;
		while(pScanB){
			if(pIntersecFunc(pScanA->m_pElem, pScanB->m_pElem, (void*)pFunction, pParam) == pScanB->m_pElem){
				pScanA = DeleteByElem(this, pScanA->m_pElem);
				pScanB = DeleteByElem(pContB, pScanB->m_pElem);
				if( (!(Card())) || (!(pContB->Card())) ) return nullptr;
			}
			else{ pScanB = pScanB->m_pNext; }
		}
		pScanA = pScanA->m_pNext;
	}

	 return nullptr;
}


void*CContainer::IntersectShipDelElemsIf(CContainer* pContShip, t_ptfVVVV pIntersecFunc, t_ptfV pFunction, void*pParam){

	assert(this!=NULL);
	assert(pContShip!=NULL);
	assert(pIntersecFunc!=NULL);

		CNode *pScan, *pShip;


		pScan = m_pHead;
		pShip = pContShip->m_pTail;

		while(pScan) {
			if(pIntersecFunc(pScan->m_pElem, pShip->m_pElem, (void*)pFunction, pParam) == pShip->m_pElem){
				pScan = DeleteByElem(this, pScan->m_pElem);
				if(!pShip->m_pPrev) { pShip = DeleteByElem(pContShip, pShip->m_pElem); }
				else 				{ pShip = DeleteByElem(pContShip, pShip->m_pPrev->m_pElem); }
				if( (!(Card())) || (!(pContShip->Card())) ) return nullptr;
			}
			else { pScan = pScan->m_pNext; }
		}

	 return nullptr;
}

int CContainer::Card() const{ return m_nCard; }
