#pragma once

#include <string>
#include <vector>
#include <memory>
#include <concepts>
#include <optional>
#include <algorithm>
#include "Component.h"

class Entity {
public:
	template<std::derived_from<AComponent> T, typename... Args>
	constexpr void AddComponent(Args&&... args) noexcept { AddComponent(std::make_unique<T>(std::forward<Args>(args)...)); }

	template<std::derived_from<AComponent> T>
	constexpr void RemoveComponent()     noexcept { RemoveComponent(T::ToEnum()); }
	constexpr void RemoveAllComponents() noexcept { m_components.clear(); }

	template<std::derived_from<AComponent> T>
	[[nodiscard]] constexpr T*    GetComponent()  const noexcept { return static_cast<T*>(GetComponent(T::ToEnum())); }
	[[nodiscard]] const auto&     GetComponents() const noexcept { return m_components; }

	template<std::derived_from<AComponent> T>
	[[nodiscard]] constexpr bool HasComponent() const noexcept { return HasComponent(T::ToEnum()).has_value(); }

	[[nodiscard]] const std::string& GetName() const noexcept { return m_name; }
	void SetName(std::string_view name)        noexcept       { m_name = name; }
private:
	 void AddComponent(std::unique_ptr<AComponent>&& component) noexcept;
	 void RemoveComponent(ComponentType type) noexcept;

	 [[nodiscard]] AComponent*              GetComponent(ComponentType type) const noexcept;
	 [[nodiscard]] std::optional<uint32_t>  HasComponent(ComponentType type) const noexcept;

	std::vector<std::unique_ptr<AComponent>> m_components;
	std::string m_name{};
};

