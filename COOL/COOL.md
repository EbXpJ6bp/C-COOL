# C 言語によるオブジェクト記述法 COOL ver.2
C-language's Object Oriented Language ver.2

+ http://www.sage-p.com/process/cool.htm

## 0. はじめに 
C 言語はオブジェクト指向言語ではないため、 オブジェクト指向に基づいた設計を記述することに 不向きです。

しかし、プラットフォームによっては、C++ 言語の処理系が無いか、 処理系に信頼の置けるものが無いために、 仕方なく C 言語を使っていることもあると思います。 そんな環境でも、オブジェクト指向の恩恵が 受けられるように、オブジェクトの記述法から、 オブジェクト特有の概念を実装するためのパターンまで説明します。

この文章は、オブジェクト指向言語を使ったことがある人を 対象にしています。

## 1. クラスの記述, 属性の記述
クラスは、構造体の発展形です。

そこで、構造体でクラスを記述します。 構造体の名前がクラス名、構造体のメンバ変数が 属性に対応しています。

	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;           /* 社員番号という属性 */
	char*  name;       /* 名前という属性 */
	} Staff;
	
クラス名、および属性名は、『名詞』にします。

クラス名は大文字から始めます。 属性名は小文字から始めます。 どちらも、複数の単語からなる場合は、 2番目以降の単語は大文字から始めます。 たとえば、firstName の N は大文字にします。

クラスは、現実にあるモノや概念またはその役割を、 属性の集りによって表現するものです。

メンバ変数は、直接更新しないで更新をする操作を 使用します。このルールさえ守るだけで、様々なメリットが生まれます。 （2章） 

処理に「必要なデータ」がどれかを1つ1つの変数ごとではなく、 「必要なオブジェクト」という意味のある大きな単位で扱うため、 依存関係を調べることが楽になります。 同様に、オブジェクト単位で有効な状態や 共有ロックを意識すれば良くなるのでユーザの負担が減ります。 （ただし、オブジェクト単位で良くなるためには、 オブジェクトが表現する概念を適切に割り当てる必要があります。） 

クラスは型であり、型から多くの実体 （インスタンス）を作ることができます。 つまり、変数宣言だけで、意味（アイデンティティ）があり、 様々なサービス（2章）を持ったインスタンスを ソースのどこにでも生成できます。 

## 2. 操作の記述 
C 言語は関数を構造体に内部に入れることができません。 そこで、関数名を、クラス名を付けた操作名 （メソッド名）にします。

 一般に、サービスと呼ばれるものを これで記述します。
 
	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;
	char*  name;
	} Staff;
	
	void Staff_init( Staff* this, int id, const char* name );
								/* 初期化する操作 */
	int  Staff_getId( Staff* this ); /* id を返す操作 */	

操作名は、『動詞』にします。

クラス名と操作名の間には '_' （アンダーライン）を 付けます。操作名は属性名と同じく小文字から始めます。 人間の言葉は、動詞（操作）より名詞（クラス）の方が 分類用の言葉が多いので、関数を特定のクラスに所属させると、 膨大になりがちな関数を適切に分類することができるようになります。 

第1引数は、必ずそのクラスへのポインタ型にします。

API のような低レベルの関数では、オブジェクトが構造体変数でなく、 識別番号やハンドルになっていることがあります。その場合、 第1引数を識別番号やハンドルにします。

操作を適切に設計すると、属性や派生属性（プロパティ）や 状態を設定/参照する操作になります（→ 5章）。 そうなると、プロセスを意識する必要がなくなるので ユーザの負担が減ります。 

1章で説明したように、メンバ変数は変更しないで、 操作の関数を通して状態を変更します。 これをカプセル化と呼びます。 カプセル化により次のメリットがあります。 

+ 引数の数が決っているので、一度に設定すべき変数の 設定のし忘れが少なくなります。 
+ 必要な出力を得るために内部的に必要なデータは、 初期化関数や別の操作関数で設定することにより、 インターフェイスの変更を最小限にすることができます。 
+ 片方を更新したときに必ず更新しなければならない別の変数がある場合、 操作の中で両方を更新するようにすれば、その注意事項を 気にしなくても良くなります。（スピード重視の設計方針の場合には、 整合性を必要とする変数が増えます）。 
+ 値の取りうる範囲の制限を操作の中でチェックするので、 制限に気を使わなくても自動的に指摘してくれます。 
+ 変数の値の変化を追跡するとき、状態設定操作に ブレークポイントを貼ったり printf 出力すれば 容易にできます。 

## 3. クラス属性の記述、定数の記述

クラスで共通に用いる変数や、クラスの定数は、 クラス属性と呼び、 C++ 言語では、static で記述します。 C 言語は、static 変数をメンバ変数の一部に 指定できないので、グローバル変数や #define マクロにします。

	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;
	char*  name;
	} Staff;
	
	extern int  Staff_n;   /* 社員数というクラス属性 */
	#define  Staff_m;      /* 社員数の最大という定数 */

操作の記述と同様に、属性名の前にクラス名を付け、 間に '_'（アンダーライン）を付けます。 属性名、定数名は、操作名と同様に小文字から始めます。

## 4. 初期化操作と後始末操作の記述
再利用の形態に応じて、以下から1つまたは複数選びます。
 
+ 処理効率優先インターフェイス 
+ 再コンパイル不要インターフェイス 
+ 動的バインディング・インターフェイス 

### 4-1.処理効率優先インターフェイス
オブジェクトを生成するコンストラクタと 削除するデストラクタは C 言語に存在しないので、 自動的に必要なところで呼び出されることはありませんが、 初期化操作と後始末操作を標準化することでカプセル化と パターン化を進めることができます。

再コンパイル不要インターフェイスや動的バインディングインターフェイスは、 処理効率優先インターフェイスの大部分を再利用するので、 まず、処理効率優先インターフェイスでクラスを作ります。 
 
この種類の操作を一覧します。
 
+ 初期化操作 init：有効な状態にする 
+ 後始末操作 finish：使わなくなったときに必要な処理をする
 
コンストラクタの代わりに初期化操作を用います。

初期化操作は、 第1引数をクラスへのポインタ型にして、 そのクラスの属性を初期化します。

	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;
	char*  name;
	} Staff;
	
	void  Staff_init( Staff* this, int id, char* name );

.		

	/*ソースファイル*/
	#include "staff.h"
	
	void  Staff_init( Staff* this, int id, char* name )
	{
	Member_init( &this->member );    /* メンバ変数の初期化 */
	
	/* その他 メンバ変数の初期化 */
	this->id = id;
	strcpy( this->name, name );
	}

初期化操作の第1引数はは、ローカル変数オブジェクトでも malloc された変数オブジェクトでも構いません。 速度の最適化を考えて、スタティック・メモリから確保した領域を 指定することもできます。

初期化関数内でメンバ変数に初期化が必要なものは、 メンバ変数の初期化が重たいものと後始末関数があるものです。 

この初期化操作など以下で説明する操作は、さまざまな初期化バリエーションを 作ることが出来ます。 

`void  Staff_initByHuman( Staff* this, Human* human );`

	/*ソースファイル*/
	void main()
	{
	Staff  a;
	Staff* b = malloc( sizeof(Staff) );
	
	Staff_init( &a, 1, "Mark" );
	Staff_init( b, 2, "Jon" );
	}


 



ハードウェアをカプセル化したオブジェクトは、初期化のタイミングで ハードウェアの独特な設定を行う必要があります。しかし、 その設定を引数に与えてしまうとオブジェクトを汎用的に 使用できなくなります。 初期化からコールバックされる関数を定義して、 そのコールバック関数の中で（デフォルトの）設定をすれば、 設定を引数に与えなくて済むようになります。 

初期化操作や生成操作やその他の操作で、malloc したり、 ファイルを開いたりした場合、 C++ 言語ではデストラクタの内部で free したり ファイルを閉じたりします。 C 言語では、後始末操作を用います。

ヒープに対する削除操作は、StdPlus_delete マクロを使って後始末関数を流用できます。

	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;
	char*  name;
	} Staff;
	
	void  Staff_finish( Staff* this );  /* 後始末 */

.

	/*ソースファイル*/
	#include "staff.h"
	
	void  Staff_finish( Staff* this )  /* 後始末 */
	{
	Member_finish( &this->member );  /* メンバ変数の後始末 */
	
	/* その他 後始末の処理 */
	}
	
後始末操作または削除操作は、必要なければ作る必要ありません。

デストラクタと異なり、自動的に呼ばれることはないので、 明示的に後始末操作または削除操作を呼び出す必要があります。

	/*ソースファイル*/
	void  main()
	{
	Staff  a;
	Staff_init( &a, 1, "Mark" );
	
	Staff_finish( &a );   /* 後始末操作を明示的に呼ぶ */
	}
	
.

	/*ソースファイル*/
	void  main()
	{
	Staff  a;
	bool   bA = false;  /* a が初期化されたかどうか */
	
	__try {
		Staff_init( &a, 1, "Mark" );
		bA = true;
	}
	__finally {
		if ( bA )  Staff_finish( &a );
	}
	}

### 4-2.再コンパイル不要インターフェイス
前節の処理効率優先インターフェイスでは、構造体のサイズが変わると 再コンパイルが必要になります。大規模のプログラムではコンパイル時間が 問題になるので、ある程度の大きさのオブジェクト（たとえばデータ層）を 再コンパイル不要インターフェイスにします。 （処理効率優先インターフェイスと共存しても構いません。）

再コンパイル不要インターフェイスでは、以下の点を注意してください。 

+ 削除操作が必須となります 
+ ヒープ領域が必須となります 
+ 処理効率優先インターフェイスより、メモリ効率、処理効率が若干落ちます 
+ 処理効率優先インターフェイスを使って呼び出したコードは一部変更が必要です。 
+ ユーザに公開するヘッダファイルに含める構造体は、メンバを定義しなくても構わなくなります。 

この種類の操作を一覧します。
 
+ 生成操作 new：領域を確保して初期化する 
+ 削除操作 delete：後始末して領域を開放する
+ 関数操作 _f：マクロ操作を関数操作に変更 

生成操作は、内部で malloc した新しいオブジェクトのアドレスを返します。

削除操作は、内部で free します。

ポインタ型を、末尾に _P を付けた名前に型定義すれば、 動的バインディング・インターフェイスと互換性を持たせることができます。

	/*ヘッダファイル*/
	/*
	*  社員クラス [Staff]
	*/
	typedef struct {
	int  id;
	char*  name;
	} Staff;
	
	typedef  Staff*   Staff_P;   /* 動的バインディング・インターフェイスとの互換 */
	
	Staff*  Staff_new( int id, char* name );
	void  Staff_delete( Staff* this );
	
.

	/*ソースファイル*/
	#include "staff.h"
	
	Staff*  Staff_new( int id, char* name );
	{
	Staff*  this = malloc( sizeof(Staff) );  /* 自分自身の生成 */
	if ( this == NULL )  error();
	
	Staff_init( this, id, name );
	
	return  this;
	}
	
	void  Staff_delete( Staff* this )
	{
	Staff_finish( this );
	free( this );  /* 自分自身の削除 */
	}

malloc, free を使わなくても、オリジナルの記憶領域管理を使用したり、 キャッシュを参照するようにしても構いません。 

その他一般的な操作において、 その実装方法がマクロで行われているときは、 関数で実装する関数操作に変更する必要があります。 これは、マクロをコンパイルするとその実装内容のコードが 操作を呼び出す側にも埋め込まれるため、 構造体の構造や操作の処理内容といった内部的な変更があったときに 再コンパイルが必要になるためです。 

	/*ヘッダファイル*/
	/****************************************
	*  <<< 設定 >>>
	*****************************************/
	/* #define  STAFF_USE_FUNC */   /* _f, _m の付かない標準インターフェイスを関数版に割り当てる */
	
	
	/****************************************
	*  <<< [Staff] >>>
	*****************************************/
	int  Staff_macro( Staff* this );
	
	int  Staff_macro_m( Staff* this );  /* マクロ版 */
	int  Staff_macro_f( Staff* this );  /* 関数版 */
	
	
	/****************************************
	*  <<< [Staff_macro] >>>
	*****************************************/
	#ifdef  STAFF_USE_FUNC
	#define  Staff_macro  Staff_macro_f
	#else
	#define  Staff_macro  Staff_macro_m
	#endif
	
	#define  Staff_macro_m( this ) \
	/* Staff_macro の実装部分をここに移動 */
	
.

	/*ソースファイル*/
	#include "staff.h"
	
	/****************************************************
	*  <<< [Staff_macro_f] Staff_macro の関数版 >>>
	*****************************************************/
	int  Staff_macro_f( Staff* this )
	{
	return  Staff_macro_m( this );
	}

処理効率優先インターフェイスから移植するときは、次の注意が必要です。 

+ オート変数（スタックに確保される変数）をポインタ型に変更します。 
+ 初期化関数 _init を生成関数 _new に変更します。 
+ 削除関数 _delete を記述するか、後始末関数 _finish を削除関数 _delete に変更します。

### 4-3.動的バインディング・インターフェイス
(第7章を理解した後で読んでください）

DLL(Dynamic Link Library) や動的リンクドライバを作成するときは、 再コンパイルも再リンクも不要となる、 動的バインディング・インターフェイスにします。 

動的バインディング・インターフェイスでは、以下の点を注意してください。 

+ 多態性のインターフェイス（→第7章）と同じ構造のスタブクラスを使ってアクセスします。 
+ 動的バインディング・クラスを使用するクラスは、スタブクラスと静的にリンクします。 
+ 動的バインディング・クラスのインターフェイスが増えても（並びが変わっても）、 再コンパイルは不要です。（その新しいインターフェイスを使わない限り） 
+ 動的バインディング・インターフェイスは、多態性を既に持っています。 
+ 呼び出し側のコードは、再コンパイル不要インターフェイスと同じにできます。 

この種類の操作を一覧します。 

+ 生成操作 new：領域を確保して初期化し、操作関数をバインドする 
+ 削除操作 delete：後始末して領域を開放する 

使用する側の互換性を保つために、インターフェイスは再コンパイル不要インターフェイスと 同じにして、処理効率優先インターフェイスを別クラスに変更します。 処理効率優先インターフェイスのクラスの名前は、Staff_Imp のように _Imp を付けます。 オブジェクトへのポインタを Staff_P のように _P を付けます。 

動的バインディングを実現するには、シンボル名の文字列から 操作関数のアドレスを内部で動的に取得する必要があります。 これを生成操作の内部で行います。

RPC(Remote Procedure Call) のシステムが使えれば、 その呼び出し方法を内部で調節することにより、サポートすることができます


	/*ヘッダファイル*/
	/************************************************************************************
	*  <<< [Staff] Staff クラスの動的バインディング・インターフェイス（スタブ） >>>
	*************************************************************************************/
	#ifdef  STAFF_STATIC_LINK
	typedef  Staff_Imp*   Staff_P;
	#else
	typedef  Inf   Staff_P;  /* Inf 構造体は第7章を参照 */
	#endif
	
	Staff_P  Staff_new( const char* className );
	void     Staff_delete( Staff_P );
	
	/* 以下は内部用 */
	extern  Staff_Sc  Staff_sc;
	
	
	/***********************************************************************
	*  <<< [Staff_delete] 削除操作（マッピングの例） >>>
	************************************************************************/
	#if  defined( STAFF_STATIC_LINK )
	#defnie  Staff_delete( this )  Staff_Imp_delete( this )
	#elif  defined( STAFF_REMOTE_LINK )
	#defnie  Staff_delete( this )  RemoteProcCall( Staff_sc.delete, this )
	#else  /* dynamic link */
	#defnie  Staff_delete( this )  Staff_sc.delete( this )
	#endif

.

	/*ソースファイル*/
	/***********************************************************************
	*  <<< [Staff_new] 生成操作 >>>
	************************************************************************/
	bool      Staff_Sc_inited = false;  /* スキーマを初期化したかどうか */
	Staff_Sc  Staff_sc;                 /* 動的バインディング・スキーマ */
	
	Staff_P  Staff_new( const char* dllPath )
	{
	Staff_P  this;
	
	#ifdef  STAFF_STATIC_LINK
	
		this = malloc( sizeof(Staff_Imp) );  /* 自分自身の生成 */
		if ( this == NULL )  error();
	
		Staff_Imp_init( this, id, name );  /* _Imp クラスに変更した処理効率優先インターフェイスをコール */
	
	#else
	
		/* スキーマの初期化（GetProcAddress を現在のタスクで必要なためここで初期化する） */
		if ( ! Staff_Sc_inited ) {
	
		HINSTANCE  DLL = Inf_AfxLoadLibrary( dllPath );
		Staff_sc->new = Inf_GetProcAddress( DLL, Staff_Imp_new );
		Staff_sc->delete = Inf_GetProcAddress( DLL, Staff_Imp_delete );
		Staff_sc->method = Inf_GetProcAddress( DLL, Staff_Imp_method );
			:           :
		（その他の操作の関数ポインタも並べる）
	
		Staff_Sc_inited = true;
		};
	
		/* ハンドルの初期化 */
		this.sc = &Staff_sc;
		#ifdef  STAFF_RIMOTE_LINK
		this.obj = RemoteProcCall( Staff_sc->new );
		#else
		this.obj = Staff_sc->new();  /* 再コンパイル不要インターフェイスの生成操作を呼び出す */
		#endif
	
	#endif
	
	return  this;
	}

静的バインディングとの互換性のために、関数ポインタを取得するマクロを以下のように用意します。

	/*Inf モジュール・ヘッダファイル*/
	HINSTANCE  Inf_AfxLoadLibrary_imp( const char* path );
	
	/***********************************************************************
	*  <<< [Inf_AfxLoadLibrary] モジュールをロードする >>>
	************************************************************************/
	#ifdef  STAFF_STATIC_LINK
	#define  Inf_AfxLoadLibrary( path )   NULL
	#else
	#define  Inf_AfxLoadLibrary( path )   Inf_AfxLoadLibrary_imp( path )
	#endif
	
	/***********************************************************************
	*  <<< [Inf_GetProcAddress] 文字列から関数のアドレスを返す >>>
	************************************************************************/
	#ifdef  STAFF_STATIC_LINK
	#define  Inf_GetProcAddress( DLL, func )   func
	#else
	#define  Inf_GetProcAddress( DLL, func )   GetProcAddress( DLL, #func )
	#endif

.
	
	/*Inf モジュール・ソースファイル*/
	/***********************************************************************
	*  <<< [Inf_AfxLoadLibrary_imp] Inf_AfxLoadLibrary の関数部分 >>>
	************************************************************************/
	HINSTANCE  Inf_AfxLoadLibrary_imp( const char* path );
	{
	HINSTANCE  DLL = AfxLoadLibrary( path );
	if ( DLL == NULL )  error();
	return  DLL;
	}
	
## 5. 状態取得操作と状態設定操作とイベントハンドラの記述 
操作が複雑にならないためには、作成するプロセスに対して最大抽象入出力 （→構造化分析／設計手法:SA/SD）を抽出し、 状態（プロパティ）に対する 操作にします。 

この種類の操作を一覧します。 

+ 状態取得操作 get 
+ 状態設定操作 set  
+ リンク状態設定操作 link 
+ イベントハンドラ on 
+ モード関数 do 

オブジェクトの状態を取得する状態取得操作(get)は、 属性（1章）を そのまま返すものがほとんどですが、複数の属性を計算した派生属性を 返すものもあります。なるべく、派生属性を返す操作をたくさん作れば、 派生属性を計算するコードがその1箇所に集ります。 検索(search, find)も状態取得操作です。特に区別する必要が無い場合を除いて、 get に統一したほうがいいでしょう。 

	int  Staff_getAge( Staff* this )
	{
	return  Date_getDiffYear( this->birth, getToday() );
	}
	
オブジェクトの状態を設定する状態設定操作(set)は、 属性間の正規状態を維持しするために、 複数の属性を設定しなければならないことあります。 属性を直接さわらないで、常に状態設定操作を使うようにすれば、 オブジェクトが異常な状態になることはありません。

	void  Staff_setBirth( Staff* this, Date* birth )
	{
	*this->birth = *birth;
	this->age = Date_getDiffYear( this->birth, getToday() );
	}
	
リンカブル・オブジェクトのリンクの状態を設定するときは、 リンク状態設定操作（link）を用います。 リンクしている状態では、 リンクされているオブジェクトが必ず存在しているように しなければならないため、特別な名前(link)を使用します。

リンクの状態を取得するときは、 一般的な状態の取得と特に扱いが変わらないので、 同じ名前(get)を使用します。

	void  Staff_linkFriend( Staff* this, Staff* friend )
	{
	this->friend = friend;
	}

イベントドリブン・スタイルで行う場合、イベント（自分以外の オブジェクトの状態変化）の通知を受ける イベントハンドラ(on)を用います。 通常、イベントハンドラの引数の形は、変化する状態を持った オブジェクトによって決められています。そして、 そのオブジェクトのイベントハンドラ登録操作によって イベントハンドラを登録するか、 通知先オブジェクト登録操作によって イベントハンドラを持つオブジェクトの 多態インターフェイスを登録します。

	void  MyWindow_onKey( MyWindow* this, int key )
	{
	}
	
	void  main()
	{
	Keybord_addOnKeyHandler( keybord, Method_Ptr(myWindow, MyWindow_onKey) );
		or
	Keybord_addTarget( keybord, MyWindow_inf_Target(myWindow) );
	}
	
イベントハンドラはユースケースに相当するので、 イベントハンドラ（関数）を汎用的に呼び出せるように再利用しようとすると、 逆に依存性が強く修正に弱いプログラムになるので注意してください。 なぜなら、イベントハンドラはいつ呼び出されるかを決めているだけで、 期待する動作を決めないためです。 再利用する場合は、イベントハンドラの内容を（構造化して） コピー＆ペーストします。 

モード関数(do)は、アプリケーション・プログラムの あるモードが終了するまで戻ってこない関数です。 この関数の内部では、ユーザや各種イベントの入力と 各イベントハンドラへのマッピングを行います。 

イベントハンドラやモード関数などの全体的なパターンは、 別紙『プログラミングスタイル CERT』を参照してください。

## 6. 集約の記述、継承の記述 
+ 集約の記述 
+ 継承の記述 
+ 多重継承の記述 
+ 重複継承の記述 
+ 動的継承の記述 

### 6-1.集約の記述
構造体を構造体に含めることで、 集約を記述します。

集約の詳細については、別紙 『プログラミングスタイル CERT』を 参照してください。

	/*ヘッダファイル*/
	typedef struct {
	int  a;
	} PartsA;
	
	typedef struct {
	int  b;
	} PartsB;
	
	typedef struct {
	PartsA  a;
	PartsB  b;
	int  m;
	} Main;

### 6-2.継承の記述
継承は、データや関数の構成をそのまま受け継ぐことによって、 クラスの性質をスーパークラスからサブクラスへ受け継ぐことです。 継承は、次のように分類されます。

+ 継承：スーパークラスが1つ 
+ 多重継承：スーパークラスが複数 
+ 重複継承：同じスーパークラスが複数 
+ 動的継承：スーパークラスと実行時に結合 

これらのうち、どれをサポートするかどうかによって、 サブクラスの記述方法はすべて異なります。 つまり、作るサブクラスは、どれをサポートするかを 決めなければなりません。ただし、大は小を兼ねるので、 動的継承や多重継承をサポートするサブクラスは 単一継承もサポート

<TABLE>
<TR><TH colspan=3>小  →  大</TH></TR>
<TR><TD rowspan=2>継承</TD><TD>多重継承</TD><TD>重複継承</TD></TR>
<TR><TD colspan=3>動的継承</TD></TR>
</TABLE>

C 言語は継承がありませんが、スーパークラスを集約することで、 仮想的に継承を実装することができます。 これは、（継承的な）委譲と呼ばれます。

単一継承的な委譲における、 スーパークラスに相当するメンバ変数は、構造体の第1メンバ変数にし、 名前は、"inherit"＋アンダーライン＋クラス名 とします。

	/*ヘッダファイル*/
	/************************************************************
	*  <<< [Super] Super クラス >>>
	*************************************************************/
	typedef struct {
	int  a;
	} Super;
	
	void  Super_method( Super*, int n );
	
	
	/************************************************************
	*  <<< [Sub] Super クラスから継承したクラス >>>
	*************************************************************/
	typedef struct {
	Super  inherit_Super;   /* スーパークラスは第1メンバ変数にする */
							/* メンバ変数名は、inherit＋クラス名 */
	int b;
	} Sub;
	
サブクラスは、スーパークラスにキャストして、スーパークラスの操作を 実行することができますが、コンパイラがプロトタイプ宣言による型チェックの 警告を出すので、マクロを定義します。 （このマクロにより、クラスを多重継承に対応するよう変更に（後述）したとき、 そのクラスを使っているソースを修正しなくて済むようにもなります。）

	/*ソースファイル*/
	/************************************************************
	*  <<< [Super] Super クラス >>>
	*************************************************************/
	#define  Super_method( this, n )  Super_method_imp( (Super*)(this), n )
	
	void  Super_method_imp( Super*, int n );  /* 内部用 */
	
	
	/************************************************************
	*  <<< [Sub] Super クラスから継承したクラス >>>
	*************************************************************/
	typedef  {
	Super  inherit_Super;
	int    n;
	} Sub;
	
	
	/************************************************************
	*  <<< 実行サンプル >>>
	*************************************************************/
	void  main()
	{
	Sub  sub;
	
	Sub_init( &sub );
	Super_method( &sub, 1 );  /* スーパークラスの操作の呼出し */
	}

### 6-3.多重継承の記述
多重継承するには仮想継承(C++ の virtual) をサポートする必要があります。 仮想継承的な委譲をサポートするスーパークラスは、 メンバ変数（下記の inherit_Super2）が構造体の第1メンバ変数でなくなるので、 スーパークラスの操作関数にメンバ変数の位置情報を渡す必要があります。 関数の実体(関数名の末尾は_imp)は、以下の引数を取ることになります。

+ 第1引数：スーパークラス・メンバ変数（下記の inherit_Super2）のアドレス
+ 第2引数：インスタンスの先頭アドレス（関数の内容に応じて省略可）
+ 第3引数：インスタンスのメモリサイズ（関数の内容に応じて省略可）
+ 第4引数以降：通常の引数

ただし、上記の引数はマクロで隠すことができるので互換性は保たれます。

	/ソースファイル*/
	/************************************************************
	*  <<< [Super2] 多重継承に対応した Super2 クラス >>>
	*************************************************************/
	void  Super2_method( Super2*, int n );     /* 公開用（プロトタイプ宣言は無くてもよい） */
	#define  Super2_method( sub, n )  \
	Super2_method_imp( &(sub)->inherit_Super2, sub, sizeof(*(sub)), n )
	
	void  Super2_method_imp( Super2*, void* obj, int size, int n ); /* 内部用 */
	
	
	/************************************************************
	*  <<< [Sub] Super2 から多重継承（仮想継承）したクラス >>>
	*************************************************************/
	typedef struct {   /* 多重継承的な委譲 */
	Super1  inherit_Super1;
	Super2  inherit_Super2;  /* virtual 継承, Super2 クラスのメンバ変数 */
	int     b;
	} Sub;
	
	
	/************************************************************
	*  <<< 実行サンプル >>>
	*************************************************************/
	void  main()
	{
	Sub  sub;
	
	Sub_init( &sub );
	sub.b = 0;
	
	sub.super.a = 1;   /* Super クラスの属性にアクセス */
	Super2_method( &sub, 1 );
	}

### 6-4.重複継承の記述
重複継承の基本は、同じスーパークラスのメンバ変数を並べることです。（重複継承は、COOL のオリジナル用語です。）

	/*ソースファイル*/
	typedef struct {   /* 多重継承的な委譲 */
	Super  inheritFor_Refer1;   /* Refer1 クラスまたは refer1 インスタンス用 */
	Super  inheritFor_Refer2;   /* Refer2 クラスまたは refer2 インスタンス用 */
	int     b;
	} Sub;
	
重複継承は、『同時』に関連を持つ複数のクラスやインスタンスが 同じスーパークラスのときに使います。（異なるスーパークラスの場合は 多重継承で済みます）。 重複継承に適するものは、リスト構造の次ポインタや双方向ポインタなどがあります。

重複継承をサポートするクラスが持つ操作関数には、 どのスーパークラス・メンバ変数を使うかを渡す必要があります。

操作関数名に Ofs を付け、第2引数にメンバ変数名を指定する 操作関数をクラスに追加します。				

	/*ソースファイル*/
	typedef struct {   /* 重複継承的な委譲 */
	Super  inheritFor_Refer1;   /* Refer1 クラスまたは refer1 インスタンス用 */
	Super  inheritFor_Refer2;   /* Refer2 クラスまたは refer2 インスタンス用 */
	int    b;
	} Sub;
	
	#define  Super_methodOfs( this, inherit, refer ) \
	Super_method_imp( &(this)->inherit, this, sizeof(*(this)), refer )
	
	void  Super_method_imp( Super2*, void* obj, int size, Refer* refer ); /* 内部用 */
	/* 多重継承用の操作関数とまったく同じものを流用できます */
	
	void  main()
	{
	Sub     sub;
	Refer   refer1;
	Refer   refer2;
	
	Super_methodOfs( &sub, inheritFor_Refer1, refer1 );
	
	#define  mb2  inheritFor_Refer2  /* メンバ変数名の短縮 */
		Super_methodOfs( &sub, mb2, refer2 );
		Super_methodOfs( &sub, mb2, refer2 );
	#undef   mb2
	}

少しでも互換性を保つ場合は、スキーマ（グローバル変数）に メンバ変数に関するオフセット情報を持つようにして、 引数にメンバ変数名を指定しなくて済む 「重複継承の多態性」（→第7章）を使用してください （ただし、グローバル変数を参照する分だけ遅くなります）。

### 6-5.動的継承の記述
動的継承（インスタンスを削除しないで型を変えること） をサポートする場合は、スーパークラスへのポインタまたはインターフェイスを 構造体に含めます。

	/*ソースファイル*/
	/************************************************************
	*  <<< [Sub] Super クラスが活性化したときのクラス >>>
	*************************************************************/
	typedef  struct {      /* 動的継承的な委譲 */
	Super*      inherit_Super;    /* スーパークラスへのポインタ */
		または
	Super_Inf   inherit_Super;    /* スーパークラスへのインターフェイス */
	
	int  n;
	} Sub;
	
	
	/************************************************************
	*  <<< 実行サンプル >>>
	*************************************************************/
	void  main()
	{
	Super   data;      /* スーパークラス（静的データ） */
	Sub     actData;   /* サブクラス（活性化状態） */
	
	Super_init( &data );
	Sub_init( &actData, &data, ... );   /* スーパークラスを引数に指定、活性化 */
	
	Sub_finish( &actData );   /* 非活性化 */
	Super_finish( &data );
	}
	
動的継承は、静的なデータをスーパークラスとして、 そのデータを活性化状態（処理中）にするときにサブクラスを使用します。 サブクラスは、スーパークラスを所有しません（後始末しません）。

この動的継承的な委譲は、活性化した後に元の型に戻る場合に適しています。 戻らない場合は、通常の単一継承的な委譲（スーパークラスの実体を持つ）を したクラスに型変換することで済むことが多いです。（メモリ的にも速度的にも）

## 7. 多態性（多相性）、 インターフェイス継承の記述
+ 多態性の記述
+ 多態性を持った生成の記述
+ 多重継承の多態性の記述
+ 重複継承の多態性の記述
+ コンテナの要素多態とコンテナ多態

### 7-1.多態性の記述
多態性は、多相性、ポリモフィズム、インターフェイス継承とも呼ばれ、 実際に実行する操作関数をオブジェクトのクラスによって実行時に切り替えます （動的バインディング）。C++ 言語の virtual 関数に相当します。

多態性は、次に示すパターンを利用して実装することができます。 （このパターンは Inf モジュールとして作られています）。

Sub1 クラスと Sub2 クラスが、Super クラスからインターフェイス継承しているとし、 共通のインターフェイス Super_method 操作の第1引数（オブジェクト）のクラスによって Sub1_method 操作と Sub2_method 操作の呼び出しを切り替えるようにしたいとして 以下に説明を続けます。

Super クラスのインターフェイス（Super_Inf）は、次のような構造体です。

	/*ヘッダファイル*/
	/************************************************************
	*  <<< [Super_Inf] Super クラスの多態インターフェイス >>>
	*************************************************************/
	typedef struct {
	Super_Sc*  sc;    /* 多態操作スキーマのアドレス（後述） */
	void*     obj;    /* オブジェクトのアドレス */
	} Super_Inf;
	
	void  Super_Inf_method( Super_Inf this );  /* Super_Inf のポインタではない */
	
インターフェイスの型名は、Xxx_Inf のようにスーパークラス名の後に、 _Inf を付けたものにします。

Super クラスのインターフェイスは、a または b に対するポインタのように扱います。 （つまり a, b の実体を削除するタイミングに注意する）。

操作の第1引数（オブジェクト）は、多態インターフェイスの 構造体へのポインタ型ではなく構造体そのものにします。 他のクラスのメンバ変数も Super_Inf クラスへのポインタではなく構造体そのものにします。

	typedef struct {
	Sub1*  a;
	} Refer;
	/************************************************************
	↓
	*************************************************************/
	typedef struct {
	Super_Inf  inf;   /* ポインタではない */
	} Refer;
	
多態操作スキーマ（または単にスキーマ）は、 関数ポインタやメモリサイズなど、サブクラスに関する情報を持つ構造体です。

	/*ヘッダファイル*/
	/*********************************************************
	*  <<< [Super_Sc] Super クラスの多態操作スキーマ >>>
	**********************************************************/
	typedef struct {
	void  (*method)();  /* 関数ポインタ */
		:       :
	（その他の操作の関数ポインタも並べる）
	
	int      size;     /* サブクラスのメモリサイズ */
	
	} Super_Sc;
	
関数ポインタ method には、Sub1_method 関数のアドレスか Sub2_method 関数のアドレスが格納されます。 これを利用して、Super_Inf_method 操作関数を実装します。

	/*ソースファイル*/
	void  Super_Inf_method( Super_Inf this )
	{
	if ( this.sc->method == NULL )  error();
	
	this.sc->method( this.obj );
	}

サブクラス（Sub1 クラスと Sub2 クラス）には、 Super クラスのインターフェイス取得関数を用意します。

	/*ソースファイル*/
	Inf_Sc  Sub1_sc;
	
	Super_Inf  Sub1_inf_Super( Sub1* this )
	{
	static  int  initialized = 0;
	Inf  inf;
	
	if ( ! initialized ) {
		Sub1_sc.method = Sub1_method;
		:           :
		（その他の操作の関数ポインタも並べる）
		（実装されていない関数には、NULL を代入します）
	
		initialized = 1;
	};
	
	inf.sc = &Sub1_sc;
	inf.obj = this;
	
	return  inf;
	}

Super_Inf クラスを使うときは、次のようにします

	/*ソースファイル*/
	typedef  struct {  /* Super クラスを参照するクラス */
	Super_Inf  super;
	} Refer;
	
	void  Refer_init( Refer*, Super_Inf super );
	
	
	void  main()
	{
	Refer      refer;
	Sub1       sub1;
	Sub2       sub2;
	Super_Inf  super;
	
	Sub1_init( &sub1 );
	super = Sub1_inf_Super( &sub1 );  /* インターフェイスを取得、構造体をそのまま代入 */
	Refer_init( &refer, super );
	Refer_run( &refer );
	
	Sub1_init( &sub2 );
	super = Sub2_inf_Super( &sub2 );
	Refer_init( &refer, super );
	Refer_run( &refer );
	}
	
	void  Refer_run( Refer* this )
	{
	Super_Inf_method( this->super );  /* 多態 */
	}
	
Refer_run 関数の中の Super_Inf_method 関数は、this->super メンバ変数が ポイントしているクラスに応じて Sub1_method 関数か Sub2_method 関数のどちらかが呼ばれます。
			
### 7-2.多態性を持った生成の記述
多態生成は、パラメタライズド・クラスを指定して インスタンスを生成し、そのインスタンスのインターフェイスを取得します。

パラメタライズド・クラスは、 スキーマへのポインタです。 スキーマ取得関数の名前は、Yyy_getSc_Xxx() のようにします。

	void  main( int argc, char* argv[] )
	{
	Xxx_Sc*  subClass;  /* パラメタライズド・クラス */
	
	subClass = Yyy_getSc_Xxx_Sc();
	
	func( subClass, argv[1] );
	}
	
	void  func( Xxx_Sc* subClass, char* name )
	{
	Xxx_Inf  inf = Xxx_Inf_new( subClass, name );  /* スーパークラスのインターフェイスを取得 */
	Xxx_Inf_method( inf, "a" );
	Xxx_Inf_delete( inf );
	}
	
多態生成をサポートするクラスとそのインターフェイスの定義の例を示します。

	/**********************************************************
	*  インターフェイス (Xxx_Inf)
	***********************************************************/
	Xxx_Inf  Xxx_Inf_new( Xxx_Sc* subClass, char* name );
	void     Xxx_Inf_delete( Xxx_Inf );
	Xxx_Inf  Xxx_Inf_init( void* union_adr, Xxx_Sc* subClass, char* name );
	void     Xxx_Inf_method( Xxx_Inf, char* s );
	
	struct _Xxx_Sc {  /* スキーマ */
	Xxx_Inf  (*new)( Xxx_Sc* subClass, char* name );             /* → Yyy_new() */
	void     (*delete)( void* obj );                              /* → Yyy_delete() */
	void     (*init)( void* obj, Xxx_Sc* subClass, char* name );  /* → Yyy_init() */
	void     (*method)( void* obj, char* s );                     /* → Yyy_method() */
	};
	
	/**********************************************************
	*  インスタンスのクラス (Yyy)
	***********************************************************/
	Yyy*     Yyy_new( Xxx_Sc* yyyClass, char* name );
	void     Yyy_delete( Yyy* );
	void     Yyy_init( Yyy*, Xxx_Sc* yyyClass, char* name );
	void     Yyy_method( Yyy*, char* s );
	
	Xxx_Sc*  Yyy_getSc_Xxx_Sc( void );
	Xxx_Inf  Yyy_inf_Xxx_Inf( Yyy* );

インターフェイスの実装の例を示します

	Xxx_Inf  Xxx_Inf_new( Xxx_Sc* subClass, char* name )
	{
	ASSERT( subClass->new != NULL );
	return  subClass->new( subClass, name );
	}
	
	void  Xxx_Inf_delete( Xxx_Inf this )
	{
	ASSERT( subClass->delete != NULL );
	this.sc->delete( this.obj );
	}
	
	Xxx_Inf  Xxx_Inf_init( void* union_adr, Xxx_Sc* subClass, char* name )
	{
	Xxx_Inf  this;
	
	ASSERT( subClass->init != NULL );
	subClass->init( union_adr, subClass, name );
	this.obj = union_adr;
	this.sc = subClass;
	
	return  this;
	}
	
	void   Xxx_Inf_method( Xxx_Inf this, char* s )
	{
	ASSERT( subClass->method != NULL );
	this.sc->method( this.obj, s );
	}
	
### 7-3.多重継承の多態性の記述
多重継承をサポートするクラスに多態性をサポートするときは、 インターフェイスのスキーマにメンバ変数へのオフセットを追加し、 インターフェイス取得関数をマクロに修正します。

また、それに伴い、スーパークラスの操作関数の引数を変更し、 それに対するスーパークラスのインターフェイスの操作関数も修正します。					

	/*ソースファイル*/
	/*********************************************************
	*  <<< [Super2_Inf] Super2 クラスのインターフェイス >>>
	**********************************************************/
	typedef struct {
	void*       obj;
	Super2_Sc*  sc;
	} Super2_Inf;
	
	typedef struct {
	Offset  offset;   /* 派生クラス(Sub)の先頭から Super2 型メンバ変数へのオフセット */
	int     size;     /* 派生クラスのメモリサイズ */
	} Super2_Sc;
	
	void  Super2_Inf_method( Super2_Inf this, int n )
	{
	Super2_method_imp( &Offset_ref( this.sc->offset, this.obj, Super2 ) ),
		this.obj, this.sc->size, n );
	}
	
	
	/*********************************************************
	*  <<< [Sub] Sub クラス >>>
	**********************************************************/
	typedef struct {   /* 多重継承的な委譲 */
	Super1  inherit_Super1;
	Super2  inherit_Super2;  /* virtual 継承, Super2 クラスのメンバ変数 */
	int     b;
	} Sub;
	
	#define  Sub_inf_Super2( this ) \
	Sub_inf_Super2_imp( this, Offset_init2( this, inherit_Super2 ) )
	
	Inf_Sc  Sub_sc;
	
	Inf  Sub_inf_Super2_imp( Sub* this, Offset offset )
	{
	static  int  initialized = 0;
	Inf  inf;
	
	if ( ! initialized ) {
		Sub_sc.method = Sub1_method;
		:           :
		（その他の操作の関数ポインタも並べる）
		（実装されていない関数には、NULL を代入します）
	
		Sub_sc.offset = offset;  /* スーパークラス・メンバ変数へのオフセット */
	
		initialized = 1;
	};
	
	inf.sc = &Sub_sc;
	inf.obj = this;
	
	return  inf;
	}
	
	
	/*********************************************************
	*  <<< [Refer] Super2 を参照するクラス >>>
	**********************************************************/
	typedef struct {
	int         data;
	Super2_Inf  super2;  /* super2 クラスから派生するインスタンスへの多態インターフェイス */
	} Refer;
	
	
	
	/*********************************************************
	*  <<< 実行サンプル >>>
	**********************************************************/
	void  main()
	{
	Refer   ref;
	Sub     sub;
	Super2_Inf  inf;
	
	Sub_init( &sub );
	inf = Sub_inf_Super2( &sub )
	
	Refer_init( &ref, inf );
	Refer_sub( &ref );
	}
	
	
	void  Refer_run( Refer* this )
	{
	Super2_Inf_method( this->super2, 3 );
	}
	
### 7-4.重複継承の多態性の記述
重複継承をサポートするクラスに多態性をサポートするときは、 多重継承をサポートするクラスのインターフェイスを取得するマクロに スーパークラス・メンバ変数を指定する引数を追加します。

それに伴い、インターフェイスを取得するマクロの呼び出し側も変更します。

	/*ソースファイル*/
	#define  Sub_inf_Super( this, inherit ) \
	Sub_inf_Super_imp( this, Offset_init2( this, inherit ) )
	
	
	typedef struct {   /* Super を参照するクラス */
	int        data;
	Super_Inf  super;  /* super クラスから派生するインスタンスへの多態インターフェイス */
	} Refer;
	
	
	void  main()
	{
	Refer      ref;
	Sub        sub;
	Super_Inf  inf;
	
	Sub_init( &sub );
	inf = Sub_inf_Super( &sub, inheritFor_Sub1 );
	
	Refer_init( &ref, inf );
	Refer_run( &ref );
	}
	
	
	void  Refer_run( Refer* this )
	{
	Super_Inf_method( this->super, 3 );
	}
	
### 7-5.コンテナの要素多態とコンテナ多態
コンテナを設計するときは、多態する位置に注意します。

多態する位置によって要素多態とコンテナ多態（スキーマ所有）と コンテナ多態（スキーマ非所有）とに分けられ、 それらは別のコンテナ・クラスになります（実装部分は一部共有できます）。

要素多態： コンテナに異なるクラスの要素が入る場合、 インターフェイスのクラス（Xxx_Inf）をコンテナに含める必要があります。 そのため、要素のクラスごとに多態性の記述コードが必要になりますが、 コンテナ多態のコンテナより柔軟性があります。 コンテナに要素を追加する関数の引数に「インターフェイス」を指定します。


	/*******************************************************
	*  <<< 要素多態のコンテナ >>>
	********************************************************/
	typedef struct {
	:
	} Container;
	
	void  Container_init( Container* );
	void  Container_add( Container*, Elem* elem, elem_type );
	void  Container_finish( Container* );
	
	/* 内部関数 */
	void  Container_add_imp( Container*, Elem_Inf );
	
	#define  Container_add( this, elem, elem_type ) \
	Container_add_imp( this, elem_type##_inf_Elem( elem ) )
	
	
	/* 実行サンプル */
	void  sample()
	{
	Container  con;
	Sub  sub;
	
	Container_init( &con );
	Container_add( &con, &sub, Sub );
	Container_finish( &con );
	}

コンテナ多態（スキーマ所有）： コンテナ（のインスタンス）に同じクラス（または多態性を持たない同じスーパークラス） の要素しか入らない場合、コンテナにインターフェイスのスキーマ（Xxx_Sc）を所有し、 型に関する情報や操作関数のポインタを格納します。 これにより、要素多態に比べて要素ごとに増えるメモリ使用量が減ります。 コンテナの初期化関数の引数に「スキーマ」を指定します

	/*******************************************************
	*  <<< コンテナ多態のコンテナ（スキーマ所有） >>>
	********************************************************/
	typedef struct {
	Container3    inherit_Container3;  /* 後記 */
	Elem_Sc*      elem_sc;
	} Container2;
	
	void  Container2_init( Container2*, elem_type );
	void  Container2_add( Container2*, Elem* elem );
	void  Container2_finish( Container2* );
	
	
	/* 内部関数（スキーマ非所有タイプの内部関数を流用できます） */
	void  Container3_init_imp( this, Offset elem_offset, int elem_size, (*Elem_method)() );
	void  Container3_add_imp( Container*, Elem* elem, void* elem_top, int elem_size, (*Elem_method)() );
	void  Container3_finish_imp( this, Offset elem_offset, int elem_size, (*Elem_method)() );
	
	
	#define  Container2_init( this, elem_type ) \
	( (this)->elem_sc = elem_type##_Sc_get_Elem(), \
		Container3_init_imp( this, (inf).elem_sc->offset, sizeof(elem_type), (this)->elem_sc->method ) )
	#define  Container2_add( this, elem ) \
	Container3_add_imp( this, &Offset_ref( (inf).sc->offset, (inf).obj, Elem ), \
		elem, sizeof(*(elem)), (inf).sc->method )
	#define  Container2_finish( this ) \
	Container3_finish_imp( this, (inf).elem_sc->offset, (inf).elem_sc->size, (inf).elem_sc->method )
	
	
	/* 実行サンプル */
	void  sample()
	{
	Container2  con;
	Sub  sub;
	
	Container2_init( &con, Sub );
	Container2_add( &con, &sub );
	Container2_finish( &con );
	}
	
コンテナ多態（スキーマ所有）の内部関数からコンテナ多態（スキーマ非所有）の 内部関数に呼び出すときは、第1引数をキャストしてください。 （両コンテナの間で多重継承することは無いため）

コンテナ多態（スキーマ非所有）： コンテナのすべての操作関数の引数に、「要素の型指定」や「スーパークラス・メンバ変数」や 「要素の操作関数指定」を指定すると、インターフェイスの互換性が低くなる代わりに、 スキーマを参照しない分、メモリ使用量、速度が良くなります。

	/*******************************************************
	*  <<< コンテナ多態のコンテナ（スキーマ非所有） >>>
	********************************************************/
	typedef struct {
		:
	} Container3;
	
	void  Container3_init( Container3*, elem_type, (*Elem_init)() );
	void  Container3_add( Container3*, Elem* elem, (*Elem_add)() );
	void  Container3_finish( Container3*, elem_type, (*Elem_finish)() );
	
	void  Container3_initOfs( Container3*, elem_type, elem_inherit, (*Elem_init)() );
	void  Container3_addOfs( Container3*, Elem* elem, elem_inherit, (*Elem_add)() );
	void  Container3_finishOfs( Container3*, elem_type, elem_inherit, (*Elem_finish)() );
	
	
	/* 内部関数（インスタンスの先頭アドレスやメモリサイズや関数ポインタを引数に持つ） */
	void  Container3_init_imp( this, Offset elem_offset, int elem_size, (*Elem_init)() );
	void  Container3_add_imp( Container*, Elem* elem, void* elem_top, int elem_size, (*Elem_add)() );
	void  Container3_finish_imp( this, Offset elem_offset, int elem_size, (*Elem_finish)() );
	
	#define  Container3_init( this, elem_type, Elem_init ) \
	Container3_init_imp( this, Offset_init( elem_type, inherit_Elem ), sizeof(elem_type), Elem_init )
	#define  Container3_add( this, elem, Elem_add ) \
	Container3_add_imp( this, &(elem)->inherit_Elem, elem, sizeof(*(elem)), Elem_add )
	#define  Container3_finish( this, elem_type, Elem_finish ) \
	Container3_finish_imp( this, Offset_init( elem_type, inherit_Elem ), sizeof(elem_type), Elem_finish )
	
	#define  Container3_initOfs( this, elem_type, elem_inherit, Elem_init ) \
	Container3_init_imp( this, Offset_init( elem_type, elem_inherit ), sizeof(elem_type), Elem_init )
	#define  Container3_addOfs( this, elem, elem_inherit, Elem_add ) \
	Container3_add_imp( this, &(elem)->elem_inherit, elem, sizeof(*(elem)), Elem_add )
	#define  Container3_finishOfs( this, elem_type, elem_inherit, Elem_finish ) \
	Container3_finish_imp( this, Offset_init( elem_type, elem_inherit ), sizeof(elem_type), Elem_finish )
	
	
	/* 実行サンプル */
	void  sample()
	{
	Container3  con;
	Sub  sub;
	
	Container3_init( &con, Sub, Sub_init );
	Container3_add( &con, &sub, Sub_add );
	Container3_finish( &con, Sub, Sub_finish );
	
	Container3_initOfs( &con, Sub, inherit_Super2, Sub_init );
	Container3_addOfs( &con, &sub, inherit_Super2, Sub_add );
	Container3_finishOfs( &con, Sub, inherit_Super2, Sub_finish );
	}
	
## 8. モジュールの記述、補助クラスの記述、カテゴリの記述
C 言語または C++ 言語では、ヘッダファイル、 ソースファイルを1セットとしたものを モジュールとします。

モジュール（ファイル名）は、クラス名と同じにします。 たとえば、Staff クラスなら staff.h と staff.c(cpp) と なります。

基本的に1モジュールに1クラスですが、 補助クラスもある場合、そのクラス名の前に モジュール名を付けます。 たとえば、補助クラス名が card なら Staff_Card というクラス名にします。 補助クラス名も大文字から始めます。 つまり、構造体の名前を Staff_Card にして、 初期化操作などの関数名を Staff_Card_init のようにします。

	Staff クラス
	Staff_Card クラス

このように、関数名やグローバル変数名の先頭をモジュール名（＝ファイル名）に 『統一』することで、その実装部分がどのファイルにあるのかすぐに分かります。

逆に MS-DOS は、ファイル名に 8文字という制限が あるので、クラス名も 8文字の短縮形にします。

クラスに属することができない関数をカテゴリごとに 集めたものをクラスと同等に扱うこともあります。 たとえば、数学関係や文字列関係、操作関係（リモート・プロシージャなど）や グローバル属性の取得設定関係（ネームサービス）などがあります。 これらは、初期化／後始末（ライフサイクル）がありません。 関数の使えない、オブジェクト指向言語では、クラスメソッドだけで 構成されるクラスになっています。

カテゴリは、Math_sin() のようにこれまで説明したクラスと同様に記述します。 ただし、初期化（生成）、後始末（削除）の操作は無く、 第1引数はオブジェクトではありません。 sin() のようにモジュール名を付けないと、 その実装部分がどのファイルにあるのかすぐに分からなくなるなどの 不都合が生じます。

## 9. COOL の特徴
C 言語によるオブジェクト記述法 COOL の特徴を挙げます。

### 1. オブジェクト指向の主要な概念をサポート
クラス（1章）、プロパティ（5章）、メソッド（2章）、 継承（6章）、多態性（7章）、をどのように記述するかを 定義しています。 これにより、C 言語だけでは表現できないオブジェクト指向的な 情報をソースコードに加えることができ、 解読するときの助けになります。

### 2. モジュール名の使用による検索性と名前衝突の回避
クラス、補助クラス（8章）、操作関数（2章）、クラス属性（3章）の 名前の先頭をモジュール名で統一することにより、それらを定義して いるプログラム・ファイルを即座に見つけることができます。

また、モジュール名はプレフィックスを兼ねるので 名前衝突の可能性が低くなります。もし衝突しても、 法則性があるので簡単なツールでモジュール名を 変更することができます。

### 3. 初期化操作の明示と、動的バインディングのサポート
初期化操作を記述法に入れることでいわゆる open-close principle が 明示され、カプセル化を進めます。 また、再コンパイル不要インターフェイスや動的バインディング・インターフェイスを 使用することにより再利用性を高めます。（4章)

### 4. 委譲と多態性による継承的再利用の促進
委譲による継承の記述は、非常に面倒ですが、 作成したクラスは、継承をサポートするクラスと同じように 使うことができます。 多重継承も Java 言語の多重インターフェイスのように 多態性の記述を用いて実現できます。 さらに、パラメタライズド・クラス を用いることにより生成時から多態性を記述でき、 重複継承や動的継承により 再利用のパターン化を進めます。（6，7章)

----------

written by M.Toda Apr.1.2000 from Nov.17.1997													  		 									