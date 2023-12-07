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
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/3ff05ca4-54f5-4ad9-8fed-5971aa87df1b.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/4abac889-ae4c-4ef5-932c-ca7a7ff85d11.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/558f2d43-0369-4fc5-a6ba-85c2d9ba6c5c.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/579c5f73-f850-4f91-b5bc-3a9b94218fb9.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/5a4a1130-60a9-40bf-9bf5-a8c3b6d3b313.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/61168175-0dcb-4466-bbe8-e5882509fe2f.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/65fe607e-6096-4683-beab-385bd48cd264.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/668262f9-6b88-44ae-8d12-1b907a4231a0.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/6c347d20-0513-4b8a-a516-82f9b80ac1c7.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/6e642511-8e25-49eb-ab17-a71c2b4fe4ae.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/78d8cecd-c4f6-4336-bfb8-ab7a9770c82e.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/7c30d358-be82-4929-8172-7c85512b4554.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/83f4db50-f72f-4b05-8b82-e74dbe904c2d.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/94a229bd-4ef7-4f7f-ad32-090e21585bed.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/b151ad65-8be9-44c1-b578-294b003b1870.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/b69da84e-9c8b-4169-9e75-d7f402d80314.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bae913ff-19e1-46d1-9802-8512b5f691ce.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bd0e1b2b-2ce5-426e-8f42-ee7550190f92.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/596/00000/bdb96c11-641f-450d-82c3-0e1b5a43d26b.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/053cbfbc-7803-45fc-b17c-a1d728b96c3f.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/21a4a724-1db4-448a-991d-6ac06a95040f.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/33a6d401-1d31-4b7f-abf1-72fa7126c57c.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/3df112c7-a753-41c2-bcd3-fe285c1e57e8.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/666214fe-408c-4ca4-a1f3-b292eaeb21bb.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/6697df46-b43d-42f0-a8b5-cb1c505c10f7.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/bf57598f-8760-4acc-8bf9-18675d761377.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/c008e1f3-fe9c-4b56-b0d0-858021aa20de.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/f17e6ab5-6e80-4049-b51d-501d9fb44e34.root",
#"/store/data/Run2023C/ZeroBias3/AOD/PromptReco-v4/000/369/585/00000/f3156ae1-cf4e-48b2-a53e-1cacfe53201b.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/0b96d595-6d8a-4626-acc0-812488037ea1.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/0cdb19dc-0e32-485c-bae1-dbe20b37c48d.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/2a0c41c0-b04b-4463-8b0d-3317fa3b1316.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/2d5df155-2920-404a-89c4-214af0ee8266.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/4916969d-f18a-456a-8576-6401ae0539a6.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/4ccb5387-83ce-4afc-bca1-973dda56f348.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/8662714a-66d6-4811-a2bf-ee4c9efb2f06.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/9e8f372c-8fbd-45fb-b3be-c887b6d1674c.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/c3dde036-e834-46e6-8869-94da65bd86f2.root",
#"/store/data/Run2023C/ZeroBias4/AOD/PromptReco-v4/000/369/585/00000/fec0c40a-fbf6-4945-be35-7ed28c782516.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/16c2f791-f385-4e11-8e98-a11f22fa25f6.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/242d758e-acdc-4b4d-bda3-5a1477490b90.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/6089b81e-4830-4610-a252-3a6651e2a115.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/83ebdf43-ba43-4ef8-b6f4-7c52d6b2b320.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/9ec3859d-40d5-424d-864f-fb6cc7b6cc29.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/a959bdeb-2322-4d9b-8b54-964acd527c45.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/b1259141-9e30-4f03-a422-a58f5d7a1898.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/dbe68128-0bd8-4ede-ab4f-bd0521276250.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/e3841c78-bcc7-4057-8f10-a9e09b571c0b.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/585/00000/efc3d0f0-eb86-4c3b-aac4-e32a7861c414.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/13837ebd-faa5-4f20-b042-80e0b0986b05.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/1905c2df-4b28-4f7c-b0bd-e6b1590c9213.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/26df49d9-c089-4676-a402-6d4d34ad0eae.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/2bba8948-a2ed-4cd3-a589-a8c75c56b0c9.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/310e854e-15bb-4e62-9565-ac70185202f9.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/3918e6d2-0457-4f31-a341-dc090a6e78b9.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/3fe00958-db2b-4bfe-b2e9-0d5374c70695.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/4a6e1c73-6b1b-4792-8d06-53bd1a806760.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/52821fc9-67bf-494e-9a2e-d3c1597ffed2.root",
#"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/52c0810a-9941-4cb8-9dea-c3957faef30e.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/55649ec2-b4b8-4f5a-869a-44a6b9fc4166.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/568b1e66-e2bd-4b79-affc-79a41d8f2845.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/5827f7d6-7cad-4f86-8581-dabd715fca39.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/5a9028fe-051f-412b-aa4a-346bf17a8f81.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/81b50f45-db17-4ed9-b63d-120e71b216a5.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/86b0d556-dc8a-4884-8169-55b1f7b8ea85.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/a89c16e5-8e57-4823-9c37-5efbe76247c7.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/a90f0c7c-21d0-4f40-830c-2aca7043a599.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/b239b90c-810c-4cc9-8ce5-08044208586f.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/c9a77906-60ac-49d6-89be-27777ed7c7d8.root",
"/store/data/Run2023C/ZeroBias5/AOD/PromptReco-v4/000/369/591/00000/d617d7ee-2f0a-4f67-92f8-2172ed67acbe.root",
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


