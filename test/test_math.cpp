#include <gtest/gtest.h>

#include <vector.h>

TEST(Math, Vec2_Addition) {
	using namespace alloy;

	const math::fvec2 a{ 0 ,0 };
	const math::fvec2 b{ 1 ,0 };

	const math::fvec2 c = a + b;

	EXPECT_EQ(c.x, a.x + b.x);
	EXPECT_EQ(c.y, a.y + b.y);
}