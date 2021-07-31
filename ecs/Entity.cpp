#include "Entity.h"

 void Entity::AddComponent(std::unique_ptr<AComponent>&& component) noexcept {
	if (HasComponent(component->GetType())) {
		return;
	}

	component->SetEntity(this);
	component->Enable();

	m_components.emplace_back(std::move(component));
}

 void Entity::RemoveComponent(ComponentType type) noexcept {
	 if (const auto index = HasComponent(type)) {
		 m_components.at(index.value())->SetEntity(nullptr);
		 m_components.erase(std::next(m_components.begin(), index.value()));
	 }
 }

 AComponent* Entity::GetComponent(ComponentType type) const noexcept {
	 if (const auto index = HasComponent(type)) {
		 return m_components.at(index.value()).get();
	 }
	 return nullptr;
 }

 std::optional<uint32_t> Entity::HasComponent(ComponentType type) const noexcept {
	 namespace rn      = std::ranges;
	 const auto lambda = [type](const auto& component) -> bool { return component->GetType() == type; };

	 if (const auto iter = rn::find_if(m_components, lambda); iter != m_components.cend()) {
		 return std::distance(m_components.begin(), iter);
	 }
	 return {};
 }
