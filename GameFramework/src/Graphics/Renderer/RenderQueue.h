#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H
#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "RenderCommand.hpp"

namespace Framework {
	namespace Graphics {
		
		class RenderQueue {
		private:
			std::vector<RenderCommand> mRenderCommands;
			
			//A vector full of indices into the mRenderCommands vector, that denote the changes in the shader bound.
			//Blocks of commands that use the same shader will be created when the queue is sorted. This vector
			//indicates where these blocks begin and end, for texture batching.
			std::vector<unsigned int> mShaderBoundaries;

		public:
			RenderQueue();
			~RenderQueue() = default;

			void submitCommand(const RenderCommand& command);
			void sort();
			void clear();

			inline RenderCommand& operator[](unsigned int index) { return mRenderCommands[index]; }
			inline unsigned int getSize() const { return mRenderCommands.size(); }
			inline std::vector<RenderCommand>& getAllCommands() { return mRenderCommands; }

		private:
			int findShaderIndex(const Shader* target, unsigned int minIndex, unsigned int maxIndex);
			int findTextureIndex(const Texture* target, unsigned int minIndex, unsigned int maxIndex);

		};

	}
}

#endif
