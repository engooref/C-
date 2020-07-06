/*
 * CContainer.h
 *
 *  Created on: 30 juin 2020
 *      Author: armand
 */

#ifndef CCONTAINER_H_
#define CCONTAINER_H_
#include <cassert>

#include <iostream>
using namespace std;


class CContainer {

	/*Class CNode Section*/
	class CNode {
	public:
		CNode * m_pPrev;
		CNode * m_pNext;
		void  * m_pElem;

	public:
		CNode();
		CNode(CNode*pPrev,CNode*pNext,void*pElem);
		~CNode();
	};

	/*Container section*/
public:
	typedef void*(*t_ptfV)(void*);
	typedef void*(*t_ptfVV)(void*, void*);
	typedef void*(*t_ptfVVV)(void*, void*, void*);
	typedef void*(*t_ptfVVVV)(void*, void*, void*, void*);


private:
	CNode *	m_pHead;
	CNode * m_pTail;
	int     m_nCard;
	t_ptfV	m_pDeleteFunc;

public:
	CContainer();
	CContainer(t_ptfV pDeleteFunc);
	~CContainer();

	void*Pushback(void*pElem);
	void*Pushfront(void*pElem);
	void*Pushat(void*pElem, int nAt);

	void*Getback();
	void*Getfront();
	void*Getat(int nAt);

	void*Popback();
	void*Popfront();
	void*Popat(int nAt);


	void* Parse(t_ptfVV pParseFunc, void*pParam);
	void* ParseDelIf(t_ptfVV pParseFunc, void* pParam);


	void*IntersectDelElemsIf(CContainer* pContB, t_ptfVVVV pIntersecFunc, t_ptfV pFunction, void* pParam);
	void*IntersectShipDelElemsIf(CContainer* pContShip, t_ptfVVVV pIntersecFunc, t_ptfV pFunction, void* pParam);

	int Card() const;

private:
	CNode*DeleteByElem(CContainer* pCont, void*pElem);
};

#endif /* CCONTAINER_H_ */
