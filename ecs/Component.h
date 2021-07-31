#pragma once

//For every Component you add, the type must be manually added to this enum.
//For now there is no way to automate this without using RTTI or adding some other kind of runtime overhead. 
enum class ComponentType { Unknown };

class Entity;
class AComponent {
public:
	virtual void Update() noexcept = 0;

	void Enable()  noexcept { m_enabled = true; }
	void Disable() noexcept { m_enabled = false; }
	[[nodiscard]] constexpr bool IsEnabled() const noexcept { return m_enabled; }

	[[nodiscard]] static constexpr ComponentType ToEnum() noexcept       { return ComponentType::Unknown; }
	[[nodiscard]] const ComponentType GetType()           const noexcept { return m_type; }

	[[nodiscard]] constexpr Entity* GetEntity() const noexcept { return m_entity; }
	void SetEntity(Entity* const entity)        noexcept       { m_entity = entity; }
protected:
	ComponentType m_type{ ComponentType::Unknown };
	Entity* m_entity{ nullptr };
	bool m_enabled{ false };
};


