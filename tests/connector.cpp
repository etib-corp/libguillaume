#include <memory>

#include <gtest/gtest.h>

#include "connector.hpp"

TEST(ConnectorTest, DefautltConstructor)
{
    std::unique_ptr<guillaume::Connector> connector = std::make_unique<guillaume::Connector>();
    EXPECT_NE(connector, nullptr);
}
