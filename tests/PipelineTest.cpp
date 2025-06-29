#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>

#include "rendering/Pipeline.h"
#include "rendering/PipelineStage.h"

namespace Boids {
namespace Rendering {
namespace Test {

// Mock Stage for testing
class MockStage : public PipelineStage {
   public:
    MockStage(const std::string& name, bool enabled = true)
        : PipelineStage(name), m_ExecuteCalled(false), m_ExecuteCount(0) {
        SetEnabled(enabled);
    }

    void Execute(Pipeline& pipeline) override {
        m_ExecuteCalled = true;
        m_ExecuteCount++;
        m_LastPipeline = &pipeline;
    }

    void OnAttach() override { m_AttachCalled = true; }

    void OnDetach() override { m_DetachCalled = true; }

    // Test helper methods
    bool WasExecuteCalled() const { return m_ExecuteCalled; }
    int GetExecuteCount() const { return m_ExecuteCount; }
    Pipeline* GetLastPipeline() const { return m_LastPipeline; }
    bool WasAttachCalled() const { return m_AttachCalled; }
    bool WasDetachCalled() const { return m_DetachCalled; }

    void Reset() {
        m_ExecuteCalled = false;
        m_ExecuteCount = 0;
        m_LastPipeline = nullptr;
        m_AttachCalled = false;
        m_DetachCalled = false;
    }

   private:
    bool m_ExecuteCalled;
    int m_ExecuteCount;
    Pipeline* m_LastPipeline;
    bool m_AttachCalled = false;
    bool m_DetachCalled = false;
};

class PipelineTest : public ::testing::Test {
   protected:
    void SetUp() override { pipeline = std::make_unique<Pipeline>(); }

    void TearDown() override { pipeline.reset(); }

    std::unique_ptr<Pipeline> pipeline;
};

// Test Pipeline construction
TEST_F(PipelineTest, Construction) {
    EXPECT_TRUE(pipeline != nullptr);

    // Test initial state
    auto& options = pipeline->GetOptions();
    EXPECT_FALSE(options.triangles);
    EXPECT_FALSE(options.texture);
    EXPECT_FALSE(options.vertices);
}

// Test adding stages
TEST_F(PipelineTest, AddStage) {
    auto stage1 = std::make_unique<MockStage>("TestStage1");
    auto stage2 = std::make_unique<MockStage>("TestStage2");

    // Capture cout output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    pipeline->AddStage(std::move(stage1));
    pipeline->AddStage(std::move(stage2));

    std::cout.rdbuf(old);

    // Verify stages were added
    EXPECT_NE(pipeline->GetStage("TestStage1"), nullptr);
    EXPECT_NE(pipeline->GetStage("TestStage2"), nullptr);
    EXPECT_EQ(pipeline->GetStage("NonExistentStage"), nullptr);

    // Verify output messages
    std::string output = buffer.str();
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Added stage 'TestStage1'"));
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Added stage 'TestStage2'"));
}

// Test removing stages
TEST_F(PipelineTest, RemoveStage) {
    auto stage1 = std::make_unique<MockStage>("TestStage1");
    auto stage2 = std::make_unique<MockStage>("TestStage2");

    pipeline->AddStage(std::move(stage1));
    pipeline->AddStage(std::move(stage2));

    // Capture cout output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    pipeline->RemoveStage("TestStage1");

    std::cout.rdbuf(old);

    // Verify stage was removed
    EXPECT_EQ(pipeline->GetStage("TestStage1"), nullptr);
    EXPECT_NE(pipeline->GetStage("TestStage2"), nullptr);

    // Verify output message
    std::string output = buffer.str();
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Removed stage 'TestStage1'"));
}

// Test enabling/disabling stages
TEST_F(PipelineTest, EnableDisableStage) {
    auto stage = std::make_unique<MockStage>("TestStage");
    auto stagePtr = stage.get();

    pipeline->AddStage(std::move(stage));

    // Capture cout output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    // Test disabling
    pipeline->EnableStage("TestStage", false);
    EXPECT_FALSE(stagePtr->IsEnabled());

    // Test enabling
    pipeline->EnableStage("TestStage", true);
    EXPECT_TRUE(stagePtr->IsEnabled());

    std::cout.rdbuf(old);

    // Verify output messages
    std::string output = buffer.str();
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Disabled stage 'TestStage'"));
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Enabled stage 'TestStage'"));
}

// Test executing pipeline with enabled stages
TEST_F(PipelineTest, ExecuteWithEnabledStages) {
    auto stage1 = std::make_unique<MockStage>("TestStage1", true);
    auto stage2 = std::make_unique<MockStage>("TestStage2", true);

    auto stage1Ptr = stage1.get();
    auto stage2Ptr = stage2.get();

    pipeline->AddStage(std::move(stage1));
    pipeline->AddStage(std::move(stage2));

    // Capture cout output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    pipeline->Execute();

    std::cout.rdbuf(old);

    // Verify stages were executed
    EXPECT_TRUE(stage1Ptr->WasExecuteCalled());
    EXPECT_TRUE(stage2Ptr->WasExecuteCalled());
    EXPECT_EQ(stage1Ptr->GetExecuteCount(), 1);
    EXPECT_EQ(stage2Ptr->GetExecuteCount(), 1);

    // Verify pipeline was passed to stages
    EXPECT_EQ(stage1Ptr->GetLastPipeline(), pipeline.get());
    EXPECT_EQ(stage2Ptr->GetLastPipeline(), pipeline.get());

    // Verify output messages
    std::string output = buffer.str();
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Executing 2 stages"));
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Executing stage 'TestStage1'"));
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Executing stage 'TestStage2'"));
}

// Test executing pipeline with disabled stages
TEST_F(PipelineTest, ExecuteWithDisabledStages) {
    auto stage1 = std::make_unique<MockStage>("TestStage1", true);
    auto stage2 = std::make_unique<MockStage>("TestStage2", false);  // Disabled

    auto stage1Ptr = stage1.get();
    auto stage2Ptr = stage2.get();

    pipeline->AddStage(std::move(stage1));
    pipeline->AddStage(std::move(stage2));

    // Capture cout output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    pipeline->Execute();

    std::cout.rdbuf(old);

    // Verify only enabled stage was executed
    EXPECT_TRUE(stage1Ptr->WasExecuteCalled());
    EXPECT_FALSE(stage2Ptr->WasExecuteCalled());
    EXPECT_EQ(stage1Ptr->GetExecuteCount(), 1);
    EXPECT_EQ(stage2Ptr->GetExecuteCount(), 0);

    // Verify output messages
    std::string output = buffer.str();
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Executing 1 stages"));
    EXPECT_THAT(output, testing::HasSubstr("Pipeline: Executing stage 'TestStage1'"));
    EXPECT_THAT(output, testing::Not(testing::HasSubstr("Pipeline: Executing stage 'TestStage2'")));
}

// Test options access
TEST_F(PipelineTest, OptionsAccess) {
    auto& options = pipeline->GetOptions();

    // Test modifying options
    options.triangles = false;
    options.texture = true;
    options.vertices = true;

    // Test const access
    const auto& constOptions = pipeline->GetOptions();
    EXPECT_FALSE(constOptions.triangles);
    EXPECT_TRUE(constOptions.texture);
    EXPECT_TRUE(constOptions.vertices);
}

// Test options reset
TEST_F(PipelineTest, OptionsReset) {
    auto& options = pipeline->GetOptions();

    // Modify options
    options.triangles = false;
    options.texture = true;
    options.vertices = true;

    // Reset options
    options.Reset();

    // Verify reset to defaults
    EXPECT_FALSE(options.triangles);
    EXPECT_FALSE(options.texture);
    EXPECT_FALSE(options.vertices);
}

}  // namespace Test
}  // namespace Rendering
}  // namespace Boids