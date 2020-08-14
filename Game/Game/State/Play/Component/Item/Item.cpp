#include "Item.h"
#include "../../../../../Framework/Framework.h"

void Item::OnHitPlayer()
{
	if (!registry)
		return;

	auto& obj = registry->get<GameObject>(m_owner);
	obj.Deactivate();
	obj.DeactivateRendering();
}
