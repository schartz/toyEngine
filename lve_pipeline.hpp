#pragma once

#include "lve_device.hpp"

#include <string>
#include <vector>

namespace lve {
    struct PipelineConfigInfo {
        VkPipelineInputAssemblyStateCreateInfo inputAssembleInfo;
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;

        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;

    };
    

    class LvePipeline {
        private:
            static std::vector<char> readFile(const std::string& filePath);
            void createGraphicsPipeline(
                const std::string& vertFilePath,
                const std::string& fragFilePath,
                const PipelineConfigInfo& configInfo);

            void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
            
            /**
             * Use refrence type member variables ONLY when it is guaranteed
             * that the referenced member variable will outlive ANY and ALL instances of 
             * the containing class which depends on it.
             * 
             **/
            LveDevice& lveDevice;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragmentShaderModule;


        public:
            LvePipeline(
                LveDevice &device,
                const std::string& vertFilePath,
                const std::string& fragFilePath,
                const PipelineConfigInfo& configInfo);
            ~LvePipeline();
            LvePipeline(const LvePipeline&) = delete;
            void operator=(const LvePipeline&) = delete;

            void bind(VkCommandBuffer commandBuffer);

            static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
    };
    
}