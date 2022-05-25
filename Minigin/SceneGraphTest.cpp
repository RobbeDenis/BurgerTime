#include "RodEnginePCH.h"
#include "SceneGraphTest.h"

void dae::SceneGraphTest::PostLoad()
{
	std::cout << "Parent: " << m_pGameObject->GetLabel() << "\n";

	std::cout << "\nChildren by index" << "\n";
	for(size_t i = 0; i < m_pGameObject->GetChildAmount(); i++)
		std::cout << "Child " << i << ": " << m_pGameObject->GetChild(i)->GetLabel() << "\n";

	std::cout << "\nChildren by label" << "\n";
	std::cout << "Child 0: " << m_pGameObject->GetChild("Child0")->GetLabel() << "\n";
	std::cout << "Child 1: " << m_pGameObject->GetChild("Child1")->GetLabel() << "\n";
	std::cout << "Child 2: " << m_pGameObject->GetChild("Child2")->GetLabel() << "\n";

	std::cout << "\nnon-exising label" << "\n";
	if(!m_pGameObject->GetChild("nullptr"))
		std::cout << "nullptr" << "\n";

	std::cout << "\nRemoving Child1 by label" << "\n";
	m_pGameObject->RemoveChild("Child1");
	for (size_t i = 0; i < m_pGameObject->GetChildAmount(); i++)
		std::cout << "Child " << i << ": " << m_pGameObject->GetChild(i)->GetLabel() << "\n";

	std::cout << "\nRemoving Child on index 1" << "\n";
	m_pGameObject->RemoveChild(1);
	for (size_t i = 0; i < m_pGameObject->GetChildAmount(); i++)
		std::cout << "Child " << i << ": " << m_pGameObject->GetChild(i)->GetLabel() << "\n";
}
