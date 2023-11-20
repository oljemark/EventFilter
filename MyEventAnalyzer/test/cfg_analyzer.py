import FWCore.ParameterSet.Config as cms

process = cms.Process("MyEventAnalyzer")

# minimum of logs
process.MessageLogger = cms.Service("MessageLogger",
  statistics = cms.untracked.vstring(),
  destinations = cms.untracked.vstring('cout'),
  cout = cms.untracked.PSet(
    threshold = cms.untracked.string('WARNING')
  )
)

#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag.globaltag = "101X_dataRun2_Express_v8"
process.GlobalTag.globaltag = "130X_dataRun3_Prompt_Candidate_2023_06_06_21_34_08"

process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
  dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
  fileNames = cms.untracked.vstring(
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/dbd5bb7f-2ab6-4613-aedc-c671ba4f467d.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/f281dce7-1339-4658-aeac-f8b9e01608f9.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/fcfd8932-e41a-4a2c-8232-db13324fb2bc.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/1f0b83f3-83cf-45e3-95d6-f07db38f1cbb.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/5e295df0-d706-468d-880b-7bc24ae25b39.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/5fae96ca-bf22-47e8-a16b-c007eef50b40.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/b09aa2a4-2cbc-47db-b02b-c5e9284e767d.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/c105ead4-b690-4b37-ae74-5bb99cddeb52.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/170c1143-e5a1-4bf2-97e7-3c1dcd1c21f3.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/1e34b9b8-09e1-44ef-acd7-2bfcc8cc23f5.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/39bdab3a-bf5c-4465-87ea-266daa37d53f.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/3de67cdf-7ad3-4172-835c-ebb716ac38ca.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/596/00000/513a1032-fbc6-48e0-8fc2-226677fec4cd.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/3ff05ca4-54f5-4ad9-8fed-5971aa87df1b.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/4abac889-ae4c-4ef5-932c-ca7a7ff85d11.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/558f2d43-0369-4fc5-a6ba-85c2d9ba6c5c.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/579c5f73-f850-4f91-b5bc-3a9b94218fb9.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/5a4a1130-60a9-40bf-9bf5-a8c3b6d3b313.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/61168175-0dcb-4466-bbe8-e5882509fe2f.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/65fe607e-6096-4683-beab-385bd48cd264.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/668262f9-6b88-44ae-8d12-1b907a4231a0.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/6c347d20-0513-4b8a-a516-82f9b80ac1c7.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/6e642511-8e25-49eb-ab17-a71c2b4fe4ae.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/78d8cecd-c4f6-4336-bfb8-ab7a9770c82e.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/7c30d358-be82-4929-8172-7c85512b4554.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/83f4db50-f72f-4b05-8b82-e74dbe904c2d.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/94a229bd-4ef7-4f7f-ad32-090e21585bed.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/b151ad65-8be9-44c1-b578-294b003b1870.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/b69da84e-9c8b-4169-9e75-d7f402d80314.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bae913ff-19e1-46d1-9802-8512b5f691ce.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bd0e1b2b-2ce5-426e-8f42-ee7550190f92.root",
"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bdb96c11-641f-450d-82c3-0e1b5a43d26b.root",
)
)

process.analyzer = cms.EDAnalyzer("MyEventAnalyzer",
  verbosity = cms.untracked.int32(0),
  tracks = cms.untracked.InputTag('ctppsLocalTrackLiteProducer'),
  tracks2 = cms.untracked.InputTag('totemRPLocalTrackFitter'),
  rpPatternTag = cms.InputTag('totemRPUVPatternFinder'),
  diagonal = cms.string("LBRT"),
  outputFileName = cms.string("output_LBRT.root"),
)

process.p = cms.Path(process.analyzer)


