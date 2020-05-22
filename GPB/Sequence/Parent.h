#ifndef INCLUDED_PARENT_H
#define INCLUDED_PARENT_H


class Select;
class Title;

class Parent {
public:
	Parent();
	~Parent();

	//parent下のシーケンス遷移
	enum SeqId {
		SEQ_TITLE,
		SEQ_SELECT,
		SEQ_GAME,

		SEQ_NONE,
	};
	void update();
	void moveTo(SeqId id);
	void setStageId(int id);
private:

	Select* mSelect;
	Title* mTitle;

	SeqId mNext;
	int mStageId;

};

#endif