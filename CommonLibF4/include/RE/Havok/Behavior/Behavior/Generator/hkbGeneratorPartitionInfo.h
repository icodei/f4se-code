#pragma once

namespace RE
{
	//Helper class to store partition indices and the number of bones mapped in those partition indices
	class hkbGeneratorPartitionInfo
	{
	public:
		//The maximum number of partitions
		enum
		{
			MAX_NUM_PARTITIONS = 32,
			MAX_NUM_BONES = 256,
		};

		//Default Constructor
		hkbGeneratorPartitionInfo();

		~hkbGeneratorPartitionInfo() {}

		/// Sets up the partition info
		void initWithPartitionIndices(const class hkaSkeleton& skeleton, const hkInt16* partitionIndices, int numPartitionIndices);

		/// Sets the partition info to be all the partitions in the skeleton
		void initWithAllPartitions(const class hkaSkeleton& skeleton);

		/// Mirror the partition info
		void mirror(const class hkaSkeleton& skeleton, const class hkaMirroredSkeleton& mirroredSkeleton);

		/// Make this partition info reflect the number of LOD bones
		void setNumLodBones(const class hkaSkeleton& skeleton, hkInt16 numLodBones);

		/// Merge in a new partition indices to the array
		void mergePartitionInfos(const class hkaSkeleton& skeleton, const hkbGeneratorPartitionInfo& info);

		/// Returns true if this generator is using partitions
		bool hasPartitions() const;

		/// Returns true if the root bone is part of the partitions
		bool hasRootBone() const;

		/// Returns true if the partition index is in this partition info
		bool hasPartitionIndex(const hkInt16 partitionIndex) const;

		/// Returns true if the bone is in this partition
		bool hasBoneIndex(const hkInt16 boneIndex) const;

		/// Check if the partitions have the same number of bones
		bool hasSameNumBones(const hkbGeneratorPartitionInfo& info, hkInt16 numBonesInOutput) const;

		/// Returns true if the partition info contains all the partitions
		bool isAllPartitions() const;

		///Get the track location in a dense partition pose from a bone index
		hkInt16 getBoneIndexFromTrackIdx(const hkaSkeleton& skeleton, const hkInt16 trackIndex) const;

		/// Returns the track offset index from the bone index
		hkInt16 getTrackIndexFromBoneIndex(hkInt16 boneIndex) const;

		/// Returns the number of bones covered by the partitions
		hkInt16 getNumBones() const;

		/// Returns the number of total possible partitions
		hkInt16 getMaxNumPartitions() const;

		/// Returns the used partitions mask
		const hkUint32* getUsedPartitionMask() const;

		/// Returns the used bone mask
		const hkUint32* getUsedBoneMask() const;

		/// Sets the number of bones covered by the partitions
		void setNumBones(const class hkaSkeleton& skeleton, hkInt16 numBones);

	private:
		/// Bones bitfield storage - can't use hkInplaceBitField since it can be serialized
		hkUint32 m_boneMask[(MAX_NUM_BONES + 31) / 32];

		/// Partition bitField storage - can't use hkInplaceBitField since it can be serialized
		hkUint32 m_partitionMask[(MAX_NUM_PARTITIONS + 31) / 32];

		/// Number of bones that can be sampled
		hkInt16 m_numBones;

		/// Total number of possible partitions
		hkInt16 m_numMaxPartitions;

	private:
		/// For the set number of LOD bones, truncate the masks so that they meet the number of new bones specified
		/// Note: This function is potentially slow
		void truncateMasksToLOD(const class hkaSkeleton& skeleton);

		/// Mask off any bones after the bone index given
		void truncateBoneMaskToNumBones(int numBones);

		/// Mask off any partitions if the start index is after the bone index
		void truncatePartitionMaskToNumBones(const class hkaSkeleton& skeleton, int numBones);
	};
}
