#include <algorithm>
#include "RenderQueue.h"
#include "Mesh.h"

namespace GF {
	namespace Graphics {

		RenderQueue::RenderQueue() {
			mRenderCommands.reserve(1000);
		}

		void RenderQueue::submitCommand(const RenderCommand& command) {
			mRenderCommands.push_back(command);
		}

		void RenderQueue::sort() {
			int index = 0;
			unsigned numCommands = (unsigned)mRenderCommands.size();

			unsigned temp = 0;

			mShaderBoundaries.push_back(0);

			//Sort by shader
			for (unsigned i = 0; i < numCommands; i++) {
				index = findShaderIndex(mRenderCommands[i].mShader, i + 1, numCommands);

				if (index != -1) {
					if (index != i + 1)
						std::iter_swap(mRenderCommands.begin() + (i + 1), mRenderCommands.begin() + index);
				}
				else
					mShaderBoundaries.push_back(i + 1);
			}

			//Sort by texture...
			for (unsigned i = 1; i < mShaderBoundaries.size(); i++) {
				for (unsigned j = mShaderBoundaries[i - 1]; j < mShaderBoundaries[i]; j++) {
					index = findTextureIndex(mRenderCommands[j].mTexture, j + 1, mShaderBoundaries[i]);

					if (index != -1 && index != j + 1)
						std::iter_swap(mRenderCommands.begin() + (j + 1), mRenderCommands.begin() + index);
				}
			}
		}

		void RenderQueue::clear() {
			mRenderCommands.clear();
			mShaderBoundaries.clear();
		}

		int RenderQueue::findShaderIndex(const Shader* target, unsigned minIndex, unsigned maxIndex) {
			for (unsigned i = minIndex; i < maxIndex; i++) {
				if (mRenderCommands[i].mShader == target)
					return i;
			}
			return -1;
		}

		int RenderQueue::findTextureIndex(const Texture* target, unsigned minIndex, unsigned maxIndex) {
			for (unsigned i = minIndex; i < maxIndex; i++) {
				if (mRenderCommands[i].mTexture == target)
					return i;
			}
			return -1;
		}


	}
}