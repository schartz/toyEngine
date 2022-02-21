#include "first_app.hpp"

#include<stdexcept>

namespace lve {
    FirstApp::FirstApp() {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    FirstApp::~FirstApp() {
        vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
        createPipeline();
        createCommandBuffers();
    }

    void FirstApp::run() {
        while(!lveWindow.shouldClose()) {
            glfwPollEvents();
        }
    }

    void FirstApp::createPipelineLayout(){
        VkPipelineLayoutCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineInfo.setLayoutCount = 0;
        pipelineInfo.pSetLayouts = nullptr;
        pipelineInfo.pushConstantRangeCount = 0;
        pipelineInfo.pPushConstantRanges = nullptr;

        if(vkCreatePipelineLayout(lveDevice.device(), &pipelineInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void FirstApp::createPipeline() {
        auto pipelineConfig = LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
        pipelineConfig.renderPass = lveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        lvePipeline = std::make_unique<LvePipeline>(
            lveDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    void FirstApp::createCommandBuffers() {}
    void FirstApp::drawFrame() {}
}